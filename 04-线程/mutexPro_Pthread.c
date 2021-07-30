// 对共享数据的操作，互斥锁

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg);
// 返回：若成功返回0，否则返回错误编号
// int pthread_join(pthread_t thread, void **retval);

int g_date = 0;
pthread_mutex_t mutex;

void * funct1(void *arg){
	printf("t1:%ld thread is create\n",(unsigned long)pthread_self());
	// printf("t1:parm= %d\n",(*(int *)arg));
	pthread_mutex_lock(&mutex);

	while(1){
		printf("t1:g_date = %d\n",g_date++);
		sleep(1);
		if(g_date==3){
			pthread_mutex_unlock(&mutex);
			printf("quit-------------------\n");
			pthread_exit(NULL);
		}
	}
}

void * funct2(void *arg){
	printf("t2:%ld thread is create\n",(unsigned long)pthread_self());
	printf("t2:parm= %d\n",(*(int *)arg));
	while(1){
		printf("t2:g_date = %d\n",g_date);
		pthread_mutex_lock(&mutex);
		g_date++;
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

int main()
{
	int ret; // 接收返回值
	int parm = 100;
	pthread_t t1; // 线程的名字
	pthread_t t2; // 线程的名字
	
	ret = pthread_create(&t1,NULL,funct1,(void *)&parm);
	if(ret==0){
		printf("main:create t1_pthread success\n");
	}

	ret = pthread_create(&t2,NULL,funct2,(void *)&parm);
	if(ret==0){
		printf("main:create t2_pthread success\n");
	}

	printf("main:%ld \n",(unsigned long)pthread_self()); //打印主线程id
	
	while(1){
	printf("main:g_date = %d\n",g_date);
	sleep(1);
		printf("------------------------------------------\n");
	}
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}
