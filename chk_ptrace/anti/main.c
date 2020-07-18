#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int debugger_is_attached(bool *res, pid_t pid);

bool is_attached = false;

pthread_mutex_t mutex_for_debugger_checker;

void *callback_func(void *arg)
{
	int err;
	while(1)
	{
		err = debugger_is_attached(&is_attached, getpid());
		if(is_attached)
		{
			fprintf(stderr, "Debugger is tested! The process will be shut dowb!\n");
			exit(0);
		}
	}
}

int main()
{
	pthread_t td;
	pthread_create(&td, NULL, callback_func, NULL);
	
	/* do something */
	sleep(5);

	/* clean up */
	printf("I exit normally!\n");
	exit(0);
	return 0;
}
