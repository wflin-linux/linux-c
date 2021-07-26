# 进程间通信原理
## 进程通信介绍(IPC)
 * ## 主要方式：管道(有名管道和无名管道)、消息队列、信号量、共享内存、Socket、Streams等。其中Socket 和 Steams 支持不同主机上的两个进程IPC

## 一、管道（通常指的是无名管道）

1.特点

   * 1、半双工（它只能用于一个方向上的传输）
   * 2、 它用于具有亲缘关系的进程之间的通信（一般父子进程或者兄弟进程之间进行通信）
   * 3、它是一种特殊的文件，对于它的读写可以普遍使用read、write等函数。但是它不是普通文件、并不属于任何文件系统、并且只是存在于内存中。
   * 4、管道中的数据被读取后管道中就没有数据了。

  原型代码

```c
#include<unistd.h>
int pipe(int fd[2]) //返回值：success 返回 0  faild 返回 -1
 // 当一个管道建立时会创建两个文件描述符：f[0]为读而打开、f[1]为写而打开。
```

## 二、FIFO

​	1.特点

   * FIFO可以在无关进程之间进行数据交换，与无名管道不同。
   * FIFO有路径名与之相关联

​     原型代码

````c
#include<sys/stat.h>
int mkfifo(const char *pathname, mode_t mode);
//实际例子 demo4.c
````

​	使用有名管道需要使用open函数打开，用一般的文件I/O操作就可以。open的用法如下：

````c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
// 实际例子 demo6.c,write.c read.c
````

​	当open一个FIFO 时，是否设置成非阻塞标志(O_NONBLOCK)的区别：

* 若没有指定的O_NINBLOCK（默认），只读open要阻塞到某个其他程序为写二打开的次FIFO，类似的，只写open要阻塞到摸个其他进程为读而打开它。
* 若是指定了O_NONBLOCK，则只读open立即返回-1，如果没有进程已经为读而打开该FIFO，其error置为ENXIO

## 三、消息队列

​	1、原理：消息队列是<font color="red"></font>，放在内核中。一个消息队列由一个标识符（即队列ID）来标识。

​	2、特点：

* 消息队列是面向记录的，其中的消息具有特定的格式以及特定的优先级
* 主要的函数：

~~~c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
// 创建打开消息：成功返回队列ID，失败返回-1
int msgget(key_t key, int msgflg);
// 添加消息：成功返回0，失败返回1
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
// 读取消息：成功返回消息长度，失败返回-1
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
// 控制消息队列：成功返回0，失败返回-1
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
~~~

* 一个案例   

  * **msgGet.c**

  ````c
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
  	msgbuf readBuf;
  	int msgId = msgget(0x1234,IPC_CREAT|0777); // 创建队列
  	if(msgId == -1){
  		printf("get que failuer\n");
  	}
  	msgrcv(msgId,&readBuf,sizeof(readBuf.mtext),888,0);		/*0 以默认的方式读取消息（阻塞）*/
  	printf("read from que:%s\n",readBuf.mtext);
  
  	return 0;
  }
  ````

  * **msgSend.c**

  ```c
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
  	msgbuf sendBuf = {888,"this is the message from quen"};
  
  	int msgId = msgget(0x1234,IPC_CREAT|0777); // 创建队列
  	if(msgId == -1){
  		printf("get que failuer\n");
  	}
  	msgsnd(msgId,&sendBuf,sizeof(sendBuf.mtext),0);		/* 非阻塞的方式发送 */
  	return 0;
  }
  ```

**在 Linux 中可以使用 vimdiff 文件1  文件2  来比较两个文件的不同之处**

### ftok 函数的简介

**系统IPC键值的格式转换函数**:系统建立IPC通讯 （[消息队列](https://baike.baidu.com/item/消息队列)、[信号量](https://baike.baidu.com/item/信号量)和[共享内存](https://baike.baidu.com/item/共享内存)） 时必须指定一个ID值。通常情况下，该id值通过ftok函数得到

> **函数原型**：key_t ftok( const char * fname, int id )     // 第二个参数只要是常量就行

**key值的构成**：在一般的UNIX实现中，是将文件的[索引节点](https://baike.baidu.com/item/索引节点)号取出，前面加上子序号得到key_t的返回值。如指定文件的索引节点号为65538，换算成16进制为0x010002，而你指定的ID值为38，换算成16进制为0x26，则最后的key_t返回值为0x26010002。

**上面的例子改进之后：**

* key_msgSend.c

```c
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

	return 0;
}
```

* key_msgGet.c

```c
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
	key_t key;
	key = ftok(".",'z');
	printf("key = %x\n",key);
	int msgId = msgget(key,IPC_CREAT|0777); // 创建队列
	if(msgId == -1){
		printf("get que failuer\n");
	}	
	msgrcv(msgId,&readBuf,sizeof(readBuf.mtext),888,0);		/*0 以默认的方式读取消息（阻塞）*/
	printf("read from que:%s\n",readBuf.mtext);
	msgsnd(msgId,&sendBuf,sizeof(sendBuf.mtext),0);

	return 0;
}
```

### msgctl 销毁队列

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 int msgctl(int msqid, int cmd, struct msqid_ds *buf);
// cmd的列表：
    IPC_STAT
    IPC_SET
    IPC_RMID			// 最常用，就是把消息队列用完之后在内核中移除
    IPC_INFD
    .......
```

