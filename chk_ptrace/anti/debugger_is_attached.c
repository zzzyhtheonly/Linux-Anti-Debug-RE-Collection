#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <error.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int debugger_is_attached(bool *res, pid_t pid)
{
	*res = false;
	char *buf;
	buf = (char*)malloc(sizeof(char)*4096);
	if(NULL == buf)
	{
		fprintf(stderr, "Checking debugger error: malloc failed!\n");
		return errno;
	}
	memset(buf, 0, sizeof(char)*4096);

	char file_name[] = "/proc/";
	char pid_buf[10] = {0};
	sprintf(pid_buf, "%d", pid);
	strcat(file_name, pid_buf);
	strcat(file_name, "/status");
	const int status_fd = open(file_name, O_RDONLY);
	if(status_fd == -1)
	{
		fprintf(stderr, "Checking debugger error: cannot open related files!\n");
		goto out;
	}

	const ssize_t num_read = read(status_fd, buf, 4096-1);
	if(num_read <= 0)
	{
		fprintf(stderr, "Checking debugger error: cannot read from related files!\n");
		goto out;
	}

	const char tracerPidString[] = "TracerPid:";
	const char *tracer_pid_ptr = strstr(buf, tracerPidString);
	if(!tracer_pid_ptr)
	{
		goto out;
	}

	for(const char *charPtr = tracer_pid_ptr + sizeof(tracerPidString) - 1;
			charPtr <= buf + num_read; ++charPtr)
	{
		if(isspace(*charPtr))
			continue;
		else
		{
			*res = isdigit(*charPtr) && *charPtr != '0';
			goto out;
		}
	}

out:
	if(close(status_fd) < 0)
	{
		fprintf(stderr, "Checking debugger error: cannot close related files!\n");
	}
	free(buf);
	return errno;
}
