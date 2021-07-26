// 创建有名管道，可以在不同的进程之间进行通信，但是一般是父子进程之间

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
// int mkfifo(const char *pathname, mode_t mode);

int main(){
	if((mkfifo("./file",0600) == -1)&& errno == EEXIST){
		printf("mkfifo faild\n");
		perror("why");
	}
	else{
		if(errno == EEXIST){
			printf("文件存在！\n");
		}
		else{
			printf("mkfifo success\n");
		}
	}
	return 0;
}
