
#define LOG_TAG "LedService"

#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>

#include <stdio.h>

#include<jni.h>  /*  /usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ */
#include <stdlib.h>

#include <android/log.h>  /* liblog */

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <sys/ioctl.h>
 #include <unistd.h>       

namespace android
{

static jint fd;

jint JNICALL ledOpen(JNIEnv *env, jclass cls)
{
	fd = open("/dev/leds",O_RDWR);

	ALOGI("native ledOpen :%d \n",fd);
	//__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native open ..,");
	
	if(fd >= 0)
		return 0;
	else
		return -1;
}

void JNICALL ledClose(JNIEnv *env, jclass cls)
{
	close(fd);
	
	ALOGI("native ledClose :%d \n",fd);
	//__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native close ..,");
}

jint JNICALL ledCtrl(JNIEnv *env, jclass cls, jint which, jint status)
{
	int ret = ioctl(fd, status, which);	

	
	ALOGI("native ledCtrl :%d LED :%d Status :%d\n",fd, which, status);
	
//	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native control %d, %d ,%d",which, status, ret);
	return ret;
}


#if 0
typedef struct {
    char *name;          /* Java里调用的函数名 */
    char *signature;    /* JNI字段描述符, 用来表示Java里调用的函数的参数和返回值类型 */
    void *fnPtr;          /* C语言实现的本地函数 */
} JNINativeMethod;
#endif

static const JNINativeMethod methods[] = {
	{"native_ledOpen",  "()I", (void *)ledOpen},
	{"native_ledClose",  "()", (void *)ledClose},
	{"native_ledCtrl",  "(II)I", (void *)ledCtrl},
};



int register_android_server_LedService(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "com/android/server/LedService",
            methods, NELEM(methods));
}

};

