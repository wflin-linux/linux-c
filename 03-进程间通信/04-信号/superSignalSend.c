#include <signal.h>
#include <stdio.h>

// int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact);

void handler(int signum, siginfo_t *info, void *context){
  printf("signum = %d\n",signum);
  if(context != NULL){
    printf("获得数据 %d",info->si_int);
    printf("获得数据 %d",info->si_value.sival_int);
  }
}


int main(){
  struct sigaction act;
  act.sa_sigaction = handler;
  act.sa_flags = SA_SIGINFO;  // 可以获取消息


  sigaction(SIGUSR1,&act,NULL); // 注册信号
  while(1);
  return 0;
}