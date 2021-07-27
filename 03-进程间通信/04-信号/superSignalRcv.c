#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


// int sigqueue(pid_t pid, int sig, const union sigval value);

int main(int argc,int **argv)
{
	int signum;
	int pid;

	signum = atoi(argv[1]);
	pid = atoi(argv[2]);

	union sigval value;
	value.sival_int = 100;

	sigqueue(pid,signum,value);
	printf("收到！");
	return 0;
}