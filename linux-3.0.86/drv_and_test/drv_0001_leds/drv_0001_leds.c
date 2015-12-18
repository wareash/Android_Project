#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>
 
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>

#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>


static struct class *cls;
static struct class_device	*cls_dev;


static int led_gpios[] = {
	EXYNOS4212_GPM4(0),
	EXYNOS4212_GPM4(1),
	EXYNOS4212_GPM4(2),
	EXYNOS4212_GPM4(3),
};



static int leds_open(struct inode *inode, struct file *file)
{
	/* ����GPIOΪ��� */
	int i = 0;
	for(i = 0; i < 4; i++)
	{
		s3c_gpio_cfgpin(led_gpios[i], S3C_GPIO_OUTPUT);
	}
	return 0;
}

/*����app  ioctl(fd, cmd, arg ) */
static long leds_ioctl(struct file *filp, unsigned int cmd,
		unsigned long arg)
{
	/*���ݴ���Ĳ���������GPIO��ƽ*/
	/* cmd :0=����,1=Ϩ�� */
	/* arg :0-3��which led */
	if(cmd !=0 && cmd !=1 )
		return -EINVAL;
	if(arg > 4)
		return -EINVAL;
	
	gpio_set_value(led_gpios[arg], !cmd);

	return 0;
}

static struct file_operations leds_fops = {
    .owner  =   THIS_MODULE,    /* ����һ���꣬�������ģ��ʱ�Զ�������__this_module���� */
    .open   =   leds_open,     
	.unlocked_ioctl	= leds_ioctl,
};


int major;
static int leds_init(void)
{
	major = register_chrdev(0, "leds_drv", &leds_fops); // ע��, �����ں�

	cls = class_create(THIS_MODULE, "leds_drv");

	cls_dev = device_create(cls, NULL, MKDEV(major, 0), NULL, "leds"); /* /dev/xyz */


	return 0;
}

static void leds_exit(void)
{
	unregister_chrdev(major, "leds_drv"); // ж��

	device_destroy(cls,  MKDEV(major, 0));
	class_destroy(cls);

}

module_init(leds_init);
module_exit(leds_exit);


MODULE_LICENSE("GPL");

