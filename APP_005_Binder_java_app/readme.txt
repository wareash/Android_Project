(1) AIDL
1. �� IHelloService.aidl ���� frameworks/base/core/java/android/os
2. �޸� frameworks/base/Android.mk  ���һ��
         core/java/android/os/IVibratorService.aidl \
+        core/java/android/os/IHelloService.aidl \

3. mmm frameworks/base

4. ��������: ./out/target/common/obj/JAVA_LIBRARIES/framework_intermediates/src/core/java/android/os/IHelloService.java

(2) Server : LedService.java 
             SystemServer.java
