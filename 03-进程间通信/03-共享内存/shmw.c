#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// int shmget(key_t key, size_t size, int shmflg);  创建共享内存，共享内存大小必须以兆对齐
// void *shmat(int shmid, const void *shmaddr, int shmflg);  连接共享内存到当前进程的地址空间
// int shmdt(const void *shmaddr);   卸载共享内存函数
// int shmctl(int shmid, int cmd, struct shmid_ds *buf);   完全清除共享内存信息。buf 里面保存卸载时的一些信息


int main(){

       char* shmataddr;
       int shmid;
       key_t key;
       key = ftok(".",1);
       
       shmid = shmget(key,1024*4,IPC_CREAT|0666);
       if (shmid == -1){
              printf("共享内存创建失败！");
              exit(-1);     // 之所以设置为 返回 -1 因为大多数的错误返回值都是 -1 ，正确返回为 0
       }
       shmataddr = shmat(shmid,0,0);
       printf("shmat ok \n");
       strcpy(shmataddr,"我是你大爷！");
       sleep(5);     // 目的是让别的程序去读它
       shmdt(shmataddr);
       shmctl(shmid,IPC_RMID,0);
       return 0;
}