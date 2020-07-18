#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched/signal.h>

static long my_pid = 0;
module_param(my_pid, long, 0);

static struct task_struct *th = NULL;

static int callback_fn(void *data)
{
	struct task_struct *tsk;
	struct thread_struct *thread;

	allow_signal(SIGKILL);
	
	if(NULL == data)
	{
		printk("No target to check, exit!\n");
		return 0;
	}

	tsk = (struct task_struct*)data;
	thread = &tsk->thread;

	while(!kthread_should_stop())
	{
		if(signal_pending(th))
		{
			printk("Checking thread receive a SIGKILL, killed\n");
			break;
		}
		
		if(tsk)
		{
			/* naive approach, if reverser starts process from gdb it would hangs */
			//thread->debugreg6 = 0;

			/* just kill the target process */
			if(thread->debugreg6 != 0)
			{
				struct pid *p = tsk->thread_pid;
				printk("Found hardware breakpoints, kill the process %d\n", tsk->pid);
				kill_pid(p, SIGKILL, 1);
				break;
			}
		}
		else
		{
			printk("Target task no longer exists, shut the checking thread\n");
			break;
		}
	}

	do_exit(0);
	return 0;
}

static int chk_hbreak_init(void)
{
	struct task_struct *tsk = pid_task(find_vpid(my_pid), PIDTYPE_PID);

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
	if(th)
	{
		kill_pid(th->thread_pid, SIGKILL, 1);
		kthread_stop(th);
	}
}

module_init(chk_hbreak_init);
module_exit(chk_hbreak_exit);
MODULE_LICENSE("GPL");
