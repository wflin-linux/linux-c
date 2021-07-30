#include <stdio.h>
#include <pthread.h>

// int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg);
// 返回：若成功返回0，否则返回错误编号

void * funct1(void *arg){
	printf("t1:%ld thread is create\n",(unsigned long)pthread_self());
	printf("t1:parm= %d\n",(*(int *)arg));
}

int main()
{
	int ret; // 接收返回值
	int parm = 100;
	pthread_t t1; // 线程的名字
	
	ret = pthread_create(&t1,NULL,funct1,(void *)&parm);

	if(ret==0){
		printf("main:create t1_pthread success\n");
	}

	printf("main:%ld \n",(unsigned long)pthread_self()); //打印主线程id

	while(1);	//防止主线程比另一个线程先退出而不打印另一个线程的信息
	return 0;
}
