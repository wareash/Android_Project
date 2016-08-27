# Copyright (C) 2012 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := HelloService.java  IHelloService.java GoodbyeService.java  IGoodbyeService.java  TestServer.java
LOCAL_MODULE := TestServer
include $(BUILD_JAVA_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := HelloService.java  IHelloService.java GoodbyeService.java  IGoodbyeService.java TestClient.java
LOCAL_MODULE := TestClient
include $(BUILD_JAVA_LIBRARY)


#nfs mount  : busybox mount -t nfs -o nolock,vers=2 192.168.1.123:/work/nfs-root /mnt
#copy file  : cp /work/android-5.0.2/out/target/product/tiny4412/system/framework/pack.jar /work/nfs-root/
#EXEC 1	    : CLASSPATH=/mnt/TestServer.jar app_process . TestServer
#EXEC 1     : CLASSPATH=/mnt/TestClient.jar app_process . TestClient  hello|hello ctq
#EXEC 2     : dalvikvm -cp /mnt/nfs-root/pack.jar ExampleDemo01 
#dir        : /work/android-5.0.2/frameworks/testing/example_java_android
#logcat     : logcat TestServer:* TestClient:* HelloService:*    *:S &


