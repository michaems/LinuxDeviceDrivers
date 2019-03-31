#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

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

/*Declare and initialize struct miscdevice*/
static struct miscdevice helloworld_miscdevice = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "my_misc_device",
    .fops = &my_dev_fops,
};

static int __init hello_init(void)
{
    int ret_val;
    pr_info("Hello World init\n");

    /*register the device with kernel*/
    ret_val = misc_register(&helloworld_miscdevice);

    if (ret_val < 0)
    {
        pr_err("Could not register the misc device mydev");
        return ret_val;
    }

    pr_info("mydev: got minor %i\n", helloworld_miscdevice.minor);

    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Hello World exit!\n");

    misc_deregister(&helloworld_miscdevice);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael M.");
MODULE_DESCRIPTION("This is the helloworld_char_driver using misc framework");

