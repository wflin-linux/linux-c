#include <stdio.h>
#include <pthread.h>

// int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg);
// void pthread_exit(void *retval);
// int pthread_join(pthread_t thread, void **retval);

// 返回：若成功返回0，否则返回错误编号

void *funct1(void *arg)
{
	static char *ret = "balalaxiaomoxian"; // 想不到啥就随便写了点。
	printf("t1:%ld thread is create\n", (unsigned long)pthread_self());
	printf("t1:parm= %s\n", (char *)arg);
	pthread_exit((void *)ret);
}

int main()
{
	int ret; // 接收返回值
	char parm[128] = "hello 你好";
	pthread_t t1; // 线程的名字
	char *pret = NULL;

	ret = pthread_create(&t1, NULL, funct1, (void *)&parm);

	if (ret == 0)
	{
		printf("main:create t1_pthread success\n");
	}

	printf("main:%ld \n", (unsigned long)pthread_self()); // 打印主线程id

	pthread_join(t1, (void **)&pret);
	printf("pret = %s\n", pret);
	return 0;
}
