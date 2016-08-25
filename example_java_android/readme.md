#compile java file with dx tool
1.javac xxx.java
2.dx --dex --output=xxx.jar xxx.class



#compile java file with android compile system
nfs mount  : busybox mount -t nfs -o nolock,vers=2 192.168.1.123:/work/nfs_root /mnt
copy file  : cp /work/android-5.0.2/out/target/product/tiny4412/system/framework/pack.jar /work/nfs-root/
EXEC 1	    : CLASSPATH=/mnt/nfs-root/pack.jar app_process . ExampleDemo01
EXEC 2     : dalvikvm -cp /mnt/nfs-root/pack.jar ExampleDemo01 
dir        : /work/android-5.0.2/frameworks/testing/example_java_android


#cat prcess name 
cd /proc/xxxx/task
for i in $(ls) ; do cat $i/comm ; done
