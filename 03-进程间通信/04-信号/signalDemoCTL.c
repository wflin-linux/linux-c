// 模拟键盘按下ctrl + c 无法停止进程

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// typedef void (*sighandler_t)(int);

// sighandler_t signal(int signum, sighandler_t handler);

// atoi() 字符串转化成整类数

// sprintf(cmd,string);就是把string作为一个指令传入到cmd里面，多用于构建脚本

int main(int argc,char **argv){
	int signum;
	int pid;
	char cmd[128];
	// 这里下标从 1 开始的原因是 程序自己也要占一位。 
	signum = atoi(argv[1]);
	pid = atoi(argv[2]);
	printf("num = %d  pid = %d\n",signum,pid);

	sprintf(cmd,"kill -%d %d",signum,pid);
	system(cmd);	// exec 族函数

	// kill(pid,signum);	//可以换一种方法去调用
	printf("send signal ok");
	return 0;
}