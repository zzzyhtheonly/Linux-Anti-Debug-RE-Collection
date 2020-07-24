#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched/signal.h>
#include <linux/delay.h>

static long my_pid = 0;
module_param(my_pid, long, 0);

static struct task_struct *th = NULL;
static int is_exit = 0;

static int callback_fn(void *data)
{
	struct task_struct *tsk;
	struct thread_struct *thread;

	allow_signal(SIGKILL);
	
	if(NULL == data)
	{
		printk("No target to check, exit!\n");
		is_exit = 1;
		return 0;
	}

	tsk = (struct task_struct*)data;
	thread = &tsk->thread;

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
			if(thread->debugreg6 != 0)
			{
				printk("Found hardware breakpoints, kill the process %d\n", tsk->pid);
				kill_pid(tsk->thread_pid, SIGKILL, 1);
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

static int chk_hbreak_init(void)
{
	struct task_struct *tsk = pid_task(find_vpid(my_pid), PIDTYPE_PID);

	if(NULL == tsk)
	{
		is_exit = 1;
		return 0;
	}

	th = kthread_run(callback_fn, (void*)tsk, "chk_hbreak");
	if(NULL == th)
	{
		printk("Failed to create kernel thread!\n");
	}

	printk("A thread starts checking for hardware breakpoint of %d\n", tsk->pid);

	return 0;
}

static void chk_hbreak_exit(void)
{
	if(!is_exit)
	{
		//kill_pid(th->thread_pid, SIGKILL, 1);
		kthread_stop(th);
	}
}

module_init(chk_hbreak_init);
module_exit(chk_hbreak_exit);
MODULE_LICENSE("GPL");
