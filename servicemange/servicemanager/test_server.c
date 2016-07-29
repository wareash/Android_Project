/* Copyright 2008 The Android Open Source Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "binder.h"

#include "test_server.h"

#define ALOGI(x...) fprintf(stderr, "svcmgr: " x)
#define ALOGE(x...) fprintf(stderr, "svcmgr: " x)

uint32_t svcmgr_lookup(struct binder_state *bs, uint32_t target, const char *name)
{
    uint32_t handle;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_string16_x(&msg, SVC_MGR_NAME);
    bio_put_string16_x(&msg, name);

    if (binder_call(bs, &msg, &reply, target, SVC_MGR_CHECK_SERVICE))
        return 0;

    handle = bio_get_ref(&reply);

    if (handle)
        binder_acquire(bs, handle);

    binder_done(bs, &msg, &reply);

    return handle;
}

int svcmgr_publish(struct binder_state *bs, uint32_t target, const char *name, void *ptr)
{
    int status;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_string16_x(&msg, SVC_MGR_NAME);
    bio_put_string16_x(&msg, name);
    bio_put_obj(&msg, ptr);

    if (binder_call(bs, &msg, &reply, target, SVC_MGR_ADD_SERVICE))
        return -1;

    status = bio_get_uint32(&reply);

    binder_done(bs, &msg, &reply);

    return status;
}

unsigned token;


void sayhello(void)
{ 
	static int cnt = 0;
	fprintf(stderr, "say hello %d \n", cnt++);
}

int sayhello_to(char *name)
{
	static int cnt = 0;
	fprintf(stderr, "say hello to %s  cnt = %d \n", name, cnt++);
	return cnt;
}
int hello_service_handler(struct binder_state *bs,
                   struct binder_transaction_data *txn,
                   struct binder_io *msg,
                   struct binder_io *reply)
{

    char name[512];	  
    struct svcinfo *si;
	uint16_t *s;
	size_t len;
	uint32_t handle;
	uint32_t strict_policy;
	int allow_isolated;
	int i;

	// Equivalent to Parcel::enforceInterface(), reading the RPC
	// header with the strict mode policy mask and the interface name.
	// Note that we ignore the strict_policy and don't propagate it
	// further (since we do no outbound RPCs anyway).
	strict_policy = bio_get_uint32(msg);

	switch(txn->code) {
	case HELLO_SVR_CMD_SAYHELLO:
    		sayhello();
		return 0;
			
    case HELLO_SVR_CMD_SAYHELLO_TO:
	 s = bio_get_string16(msg, &len);
        if (s == NULL) {
            return -1;
        }
	for (i=0; i<len; i++)
		name[i] = s[i];
	name[i] = '\0';

	/* call function to deal */
	i = sayhello_to(name);
	
	
	/* put result to reply */
	bio_put_uint32(reply, i);
//	ALOGE(" sayhello_to return value = %d\n", i);   
	break;
		
    default:
        ALOGE("unknown code %d\n", txn->code);
        return -1;

   }
    return 0;
}
int main(int argc, char **argv)
{
    int fd,ret;
    struct binder_state *bs;
    uint32_t svcmgr = BINDER_SERVICE_MANAGER;
    uint32_t handle;

    bs = binder_open(128*1024);
    if (!bs) {
        fprintf(stderr, "failed to open binder driver\n");
        return -1;
    }

	/*add server*/
	ret = svcmgr_publish(bs, svcmgr, "hello", (void *)123);
	if (ret) {
	    fprintf(stderr, "failed to publish hello services\n");
	    return -1;
	}
	
	svcmgr_publish(bs, svcmgr, "goodbye", (void *)123);
	if (ret) {
	    fprintf(stderr, "failed to publish goodbye services\n");
	    return -1;
	}
	#if 0
	while(1)
	{
		/*read data*/
		/*prase data,and process data*/
		/*reply data*/
	}
	#endif
	binder_loop(bs, hello_service_handler);

    return 0;
}
