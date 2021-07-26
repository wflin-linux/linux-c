// 创建有名管道，可以在不同的进程之间进行通信，但是一般是父子进程之间

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

// int mkfifo(const char *pathname, mode_t mode);

int main(){
	mkfifo("./file",0600);
	return 0;
}
