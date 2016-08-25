#nfs mount  : busybox mount -t nfs -o nolock,vers=2 192.168.1.123:/work/nfs_root /mnt
#copy file  : cp /work/android-5.0.2/out/target/product/tiny4412/system/framework/pack.jar /work/nfs-root/
#EXEC 1	    : CLASSPATH=/mnt/nfs-root/pack.jar app_process . ExampleDemo01
#EXEC 2     : dalvikvm -cp /mnt/nfs-root/pack.jar ExampleDemo01 
#dir        : /work/android-5.0.2/frameworks/testing/example_java_android
