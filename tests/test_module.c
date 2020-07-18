#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int test_init(void)
{
	printk("Test module init!\n");
	return 0;
}

static void test_exit(void)
{
	printk("Test module exit!\n");
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
