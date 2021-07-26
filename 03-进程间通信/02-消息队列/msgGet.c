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

// 现在把key 写死的 就是那个888 887，后面可以用函数(ftok)生成key
int main(){
	msgbuf readBuf,sendBuf={887,"我收到消息了"};
	int msgId = msgget(0x1234,IPC_CREAT|0777); // 创建队列
	if(msgId == -1){
		printf("get que failuer\n");
	}	
	msgrcv(msgId,&readBuf,sizeof(readBuf.mtext),888,0);		/*0 以默认的方式读取消息（阻塞）*/
	printf("read from que:%s\n",readBuf.mtext);
	msgsnd(msgId,&sendBuf,sizeof(sendBuf.mtext),0);

	return 0;
}

// 互通的话不能把消息类型设置为一样，如果设置为一样就是自己读自己，就成了一个环