/* Copyright 2008 The Android Open Source Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "binder.h"
#include "test_server.h"


struct binder_state *g_bs;
uint32_t g_handle;

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
void sayhello(void)  // refre to svcmgr_lookup
{
	unsigned iodata[512/4];
	struct binder_io msg, reply;
	
	/* creat a binder_io */
	bio_init(&msg, iodata, sizeof(iodata), 4);
	bio_put_uint32(&msg, 0);  // strict mode header

	/* put args in binder_io */

	/* call binder_call */
	binder_call(g_bs, &msg, &reply, g_handle, HELLO_SVR_CMD_SAYHELLO);
	
	/* replay from server, and prase return value */

	binder_done(g_bs, &msg, &reply);

}
int  sayhello_to(char *name)
{
	unsigned iodata[512/4];
	struct binder_io msg, reply;
	int ret;
	
	/* creat a binder_io */
	bio_init(&msg, iodata, sizeof(iodata), 4);
	bio_put_uint32(&msg, 0);  // strict mode header

	/* put args in binder_io */
	bio_put_string16_x(&msg, name);
	
	/* call binder_call */
	if (binder_call(g_bs, &msg, &reply, g_handle, HELLO_SVR_CMD_SAYHELLO))
	    return 0;
	
	/* replay from server, and prase return value */
	ret = bio_get_uint32(&reply);
	
	binder_done(g_bs, &msg, &reply);

	return ret;
}

/*
  * ./hello_client hello 
  * ./hello_client hello <name>
  */

int main(int argc, char **argv)
{
	int fd;
	struct binder_state *bs;
	uint32_t svcmgr = BINDER_SERVICE_MANAGER;
	uint32_t handle;
	int ret;

	bs = binder_open(128*1024);
	if (!bs) {
	    fprintf(stderr, "failed to open binder driver\n");
	    return -1;
	}
	g_bs = bs;
	/* get service */
	handle = svcmgr_lookup(bs, svcmgr, "hello");
	if (!handle)
	{
	    fprintf(stderr, "failed to svcmgr_lookup\n");
	    return -1;
	}
	g_handle = handle;
	/* send data to server */
	if(argc==2)
	{
		sayhello();
	}else if (argc==3)
	{
		ret = sayhello_to(argv[2]);
		fprintf(stderr, "get ret from sayhello_to %d  \n", ret);
	}

	binder_release(g_bs, g_handle);
	return 0;
}
