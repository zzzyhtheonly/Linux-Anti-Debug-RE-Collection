#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xb90cb2c6, "module_layout" },
	{ 0x70386c6e, "find_vpid" },
	{ 0x3edbeb0f, "pv_ops" },
	{ 0x8dd184de, "kthread_create_on_node" },
	{ 0xc5850110, "printk" },
	{ 0xe0bcb46d, "kthread_stop" },
	{ 0x26a4aba5, "kill_pid" },
	{ 0x6d5bd95a, "pid_task" },
	{ 0x952664c5, "do_exit" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x519fd0d1, "wake_up_process" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x6df1aaf1, "kernel_sigaction" },
	{ 0x75c18f3, "param_ops_long" },
};

MODULE_INFO(depends, "");

