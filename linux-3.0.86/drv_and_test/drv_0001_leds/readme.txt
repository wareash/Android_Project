可以编译进内核
修改 .../xxxx_kernel/drivers/char/Makefile
		添加 obj-y                           += drv_0001_leds.o
		
也可以单独编译测试：
利用Makefile to make