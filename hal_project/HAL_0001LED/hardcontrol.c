
#include<jni.h>  /*  /usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ */
#include<stdio.h>
#include <stdlib.h>

#include <android/log.h>  /* liblog */

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <sys/ioctl.h>
 #include <unistd.h>       

//__android_log_print(ANDROID_LOG_DEBUG, );

static jint fd;

jint JNICALL ledOpen(JNIEnv *env, jclass cls)
{
	fd = open("/dev/leds",O_RDWR);
	
	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native open ..,");
	
	if(fd >= 0)
		return 0;
	else
		return -1;
}

void JNICALL ledClose(JNIEnv *env, jclass cls)
{
	close(fd);
	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native close ..,");
}

jint JNICALL ledCtl(JNIEnv *env, jclass cls, jint which, jint status)
{
	int ret = ioctl(fd, status, which);	
	
	__android_log_print(ANDROID_LOG_DEBUG, "LEDDemo", "native control %d, %d ,%d",which, status, ret);
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
	{"ledOpen",  "()I", (void *)ledOpen},
	{"ledClose",  "()", (void *)ledOpen},
	{"ledCtl",  "(II)I", (void *)ledOpen},
};



JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;
	jclass cls;
	if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4)) {
		return JNI_ERR; /* JNI version not supported */
	}
	cls = (*env)->FindClass(env, "com/example/hardlibrary/HardControl");
	if (cls == NULL) {
		return JNI_ERR;
	}
	
	/* 2.mapping java hello -> c_hello */
	if (((*env)->RegisterNatives(env, cls, methods, sizeof(methods)/sizeof(methods[0])) < 0)) 
		{
			printf("JNI ERROR");
			return JNI_ERR;
		}
	
	return JNI_VERSION_1_4;
}
