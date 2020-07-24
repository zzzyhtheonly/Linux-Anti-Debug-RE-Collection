#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched/signal.h>
#include <linux/ptrace.h>
#include <linux/delay.h>

static long my_pid = 0;
module_param(my_pid, long, 0);

static struct task_struct *th = NULL;
static int is_exit = 0;

static int callback_fn(void*);

static int chk_ptrace_init(void)
{
	struct task_struct *tsk = pid_task(find_vpid(my_pid), PIDTYPE_PID);

	if(NULL == tsk)
	{
		is_exit = 1;
		return 0;
	}

	th = kthread_run(callback_fn, (void*)tsk, "chk_ptrace");
	if(NULL == th)
	{
		printk("Failed to create kernel thread!\n");
	}

	printk("A thread starts checking for ptrace flag of %d\n", tsk->pid);
	return 0;
}

static void chk_ptrace_exit(void)
{
	if(!is_exit)
	{
		//kill_pid(th->thread_pid, SIGKILL, 1);
		kthread_stop(th);
	}
}

static int callback_fn(void *data)
{
	struct task_struct *tsk;

	if(NULL == data)
	{
		printk("No target to check, exit!\n");
		is_exit = 1;
		return 0;	
	}

	tsk = (struct task_struct*)data;

	allow_signal(SIGKILL);

	while(!kthread_should_stop())
	{
		#if 0	
		if(signal_pending(th))
		{
			printk("Checking thread receive a SIGKILL, killed\n");
			is_exit = 1;
			break;
		}
		#endif

		if(tsk)
		{
			if(tsk->ptrace & PT_PTRACED)
			{
				kill_pid(tsk->thread_pid, SIGKILL, 1);
				printk("Ptrace flag found, killed target process\n");
				is_exit = 1;
				break;
			}
		}		
		else
		{
			printk("Target task no longer exists, shut the checking thread\n");
			is_exit = 1;
			break;
		}

		ssleep(1);
		
	}

	return 0;
}

module_init(chk_ptrace_init);
module_exit(chk_ptrace_exit);
MODULE_LICENSE("GPL");
