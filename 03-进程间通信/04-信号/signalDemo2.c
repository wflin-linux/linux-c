// 模拟键盘按下ctrl + c 无法停止进程

#include <signal.h>
#include <stdio.h>

// typedef void (*sighandler_t)(int);

// sighandler_t signal(int signum, sighandler_t handler);

// 修改默认的处理函数，也就是如果按ctrl+c 就执行handler函数不结束。
void handler (int signum){
	printf("get signum = %d\n",signum);
	switch(signum){
		case 2:
			printf("SIGINT\n");
			break;
		case 9:
			printf("SIGKILL\n");
			break;
		case 10:
			printf("SIGUSR1\n");
			break;
	}
	printf("never quit\n");
}

int main(){
	signal(SIGINT,handler);	//信号注册
	signal(SIGKILL,handler);
	signal(SIGUSR1,handler);
	while(1);
	return 0;
}