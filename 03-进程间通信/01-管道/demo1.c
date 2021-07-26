// 创建无名管道

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


/* 
 * int pipe(int pipefd[2]);
 * int mkfifo(const char *pathname, mode_t mode);
*/

int main()
{
	int fd[2];
	char* str = "hello from father";
    char buff[128];

	// 创建管道
	if(pipe(fd)==-1){
		printf("create pip failed");
    }

	//创建进程
    int pid = fork();

	// 进程创建失败
    if(pid<0){
    	printf("create child failed\n");
    }

	// 父进程
    else if(pid>0){
    	printf("this is father pid\n");
		close(fd[0]);  //关闭读，打开写
		write(fd[1],str,strlen(str));
		wait(NULL);  // 等待子进程退出
    }

	// 子进程
	else{
    	printf("this is chlid\n");
	close(fd[1]);  //关闭写，打开读
	read(fd[0],buff,128);
    printf("read from father: %s \n",buff);
	exit(0);
	}
    return 0;
}
