#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/notifier.h>

int module_notifier(struct notifier_block *nb, unsigned long action, void *data);

struct notifier_block nb = 
{
	.notifier_call = module_notifier,
	.priority = INT_MAX
};

int fake_module_init(void)
{
	printk("Module %s has been hooked!\n", THIS_MODULE->name);
	return 0;
}

void fake_module_exit(void)
{
	printk("Hooked module %s will exit!\n", THIS_MODULE->name);
}

int module_notifier(struct notifier_block *nb, unsigned long action, void *data)
{
	struct module *module;
	unsigned long flags = 0;
	DEFINE_SPINLOCK(module_notifier_spinlock);

	module = (struct module*)data;

	if(NULL == module)
	{
		printk("Why pass me a illegal module? GET OUT OF HERE!\n");
		return NOTIFY_DONE;
	}

	printk("Processing the module: %s\n", module->name);

	spin_lock_irqsave(&module_notifier_spinlock, flags);

	switch(module->state)
	{
		case MODULE_STATE_COMING:
			module->init = fake_module_init;
			module->exit = fake_module_exit;
			break;
		default: break;
	}

	spin_unlock_irqrestore(&module_notifier_spinlock, flags);

	return NOTIFY_DONE;
}

static int shut_modules_init(void)
{
	register_module_notifier(&nb);
	return 0;
}

static void shut_modules_exit(void)
{
	unregister_module_notifier(&nb);
	return;
}

module_init(shut_modules_init);
module_exit(shut_modules_exit);
MODULE_LICENSE("GPL");
