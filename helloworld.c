#include <linux/init.h>
#include <linux/module.h>

#include <linux/cdev.h>
#include <linux/fs.h>

#include <linux/device.h>

#define DEVICE_NAME "mish_device"
#define CLASS_NAME "hello_class"

#define MY_MAJOR_NUM 202

static struct class* helloClass;
static struct cdev my_dev;
dev_t dev;

static int my_dev_open(struct inode *inode, struct file *file)
{
	pr_info("my_dev_open() is called.\n");
	return 0;
}

static int my_dev_close(struct inode *inode, struct file *file)
{
	pr_info("my_dev_close() is called.\n");
	return 0;
}

static long my_dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	pr_info("my_dev_ioctrl() is called. cmd=%d, arg=%ld\n", cmd, arg);
	return 0;
} 

/*Declare a file_operations structure*/
static const struct file_operations my_dev_fops = {
	.owner = THIS_MODULE,
	.open = my_dev_open,
	.release = my_dev_close,
	.unlocked_ioctl = my_dev_ioctl,
};


static int __init hello_init(void)
{
	int ret;
    dev_t dev_no;
	int Major;

	struct device* helloDevice;

	pr_info("Hello World init\n");

	ret = alloc_chrdev_region(&dev_no, 0, 1, DEVICE_NAME);

	Major = MAJOR(dev_no);
	
	dev = MKDEV(Major, 0);

	cdev_init(&my_dev, &my_dev_fops);
	ret = cdev_add(&my_dev, dev, 1);

	helloClass = class_create(THIS_MODULE, CLASS_NAME);

	helloDevice = device_create(helloClass, NULL, dev, NULL, DEVICE_NAME);

	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("Hello World exit...\n");

	cdev_del(&my_dev);
	unregister_chrdev_region(MKDEV(MY_MAJOR_NUM, 0), 1);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael M.");
MODULE_DESCRIPTION("This is a module that interacts with the ioctrl system call");

