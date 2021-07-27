#include <signal.h>
#include <stdio.h>
int main(){

       signal(SIGKILL,SIG_IGN); // 杀死依然无法忽略
       signal(SIGINT,SIG_IGN);
       while(1);
       return 0;
}