#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// int msgget(key_t key, int msgflg);	/*创建一个消息队列*/
// int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);	/*发送一个消息*/
// ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);	/*接收消息*/

typedef struct msgbuf {
              long mtype;       /* message type, must be > 0 */
              char mtext[128];    /* message data */
}msgbuf;

int main(){
	msgbuf readBuf,sendBuf = {888,"this is the message from quen"};
	key_t key;
	key = ftok(".",'z');
	printf("key = %x\n",key);
	int msgId = msgget(key,IPC_CREAT|0777); // 创建队列
	if(msgId == -1){
		printf("get que failuer\n");
	}
	msgsnd(msgId,&sendBuf,sizeof(sendBuf.mtext),0);		/* 非阻塞的方式发送 */
	msgrcv(msgId,&readBuf,sizeof(readBuf.mtext),887,0);
	printf("return from get : %s \n",readBuf.mtext);
	msgctl(msgId,IPC_RMID,NULL);
	return 0;
}