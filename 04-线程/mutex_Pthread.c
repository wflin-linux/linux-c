// 互斥锁，运行完一个线程之后才能运行另一个线程

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg);
// 返回：若成功返回0，否则返回错误编号
// int pthread_join(pthread_t thread, void **retval);

// int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
// int pthread_mutex_destroy(pthread_mutex_t mutex);

// int pthread_mutex_lock(pthread_mutex_t mutex);
// int pthread_mutex_trylock(pthread_mutex_t mutex);
// int pthread_mutex_unlock(pthread_mutex_t mutex);

pthread_mutex_t mutex;

void *funct1(void *arg)
{
	pthread_mutex_lock(&mutex); // 加锁
	printf("t1:%ld thread is create\n", (unsigned long)pthread_self());
	printf("t1:parm= %d\n", (*(int *)arg));
	pthread_mutex_unlock(&mutex); // 解锁
}

void *funct2(void *arg)
{
	pthread_mutex_lock(&mutex); //  加锁
	printf("t2:%ld thread is create\n", (unsigned long)pthread_self());
	printf("t2:parm= %d\n", (*(int *)arg));
	pthread_mutex_unlock(&mutex); // 解锁
}

int main()
{
	int ret; // 接收返回值
	int parm = 100;
	pthread_t t1; // 线程的名字
	pthread_t t2; // 线程的名字

	pthread_mutex_init(&mutex, NULL); //创建锁

	ret = pthread_create(&t1, NULL, funct1, (void *)&parm);
	if (ret == 0)
	{
		printf("main:create t1_pthread success\n");
	}

	ret = pthread_create(&t2, NULL, funct2, (void *)&parm);
	if (ret == 0)
	{
		printf("main:create t2_pthread success\n");
	}

	printf("main:%ld \n", (unsigned long)pthread_self()); //打印主线程id

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mutex); // 销毁锁
	return 0;
}
