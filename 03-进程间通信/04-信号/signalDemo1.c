// 模拟键盘按下ctrl + c 无法停止进程

#include <signal.h>
#include <stdio.h>

// typedef void (*sighandler_t)(int);

// sighandler_t signal(int signum, sighandler_t handler);

// 修改默认的处理函数，也就是如果按ctrl+c 就执行handler函数不结束。
void handler (int signum){
	printf("get signum = %d\n",signum);
	printf("never quit\n");
}

int main(){
	signal(SIGINT,handler);	//信号注册
	while(1);
	return 0;
}