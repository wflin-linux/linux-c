// 创建有名管道，可以在不同的进程之间进行通信，但是一般是父子进程之间
//希望文件存在的时候不出错,没有文件自动创建

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<errno.h>



// int mkfifo(const char *pathname, mode_t mode);

int main(){
	if(( mkfifo("./file",0600) == -1 )&& errno!=EEXIST){
		printf("mkfifo failuer\n");	
		perror("why");
	}
	return 0;
}
