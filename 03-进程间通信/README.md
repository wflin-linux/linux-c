# 进程间通信方式
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



## 四、共享内存

* **常用api**

  ```c
  #include <sys/ipc.h>
  #include <sys/shm.h>
  
  // 创建或获取一个共享内存：成功返回共享内存ID，失败返回 -1
  int shmget(key_t key, size_t size, int shmflg);
  
  // 连接共享内存到当前进程的地址空间：成功返回指向共享内存的指针，失败返回 -1
  void *shmat(int shmid, const void *shmaddr, int shmflg);
  
  // 断开与共享内存的连接：成功返回0，失败返回 -1
  int shmdt(const void *shmaddr);
  
  // 控制共享内存相关信息：成功返回0，失败返回-1
  int shmctl(int shmid, int cmd, struct shmid_ds *buf);
  ```


## 五、信号

[推荐博文](https://www.jianshu.com/p/f445bfeea40a)

对于Linux来说，实际的信号是软中断，喜多重要程序都需要信号处理。信号，为Linux提供了一种处理异步事件的方法。比如，终端用户输入了ctrl + c 来中断程序，会通过信号机制停止一个程序。

### **信号的概述**：

**1、信号的名字和编号：**每个信号都有一个名字和编号，这些名字都以“SIG”开头，例如“SIGIO ”、“SIGCHLD”等等。信号名都定义为正整数。 具体的信号名称可以使用`kill -l`来查看信号的名字以及序号，信号是从1开始编号的，不存在0号信号。kill对于信号0又特殊的应用，用于系统层面的中断。

应用层来说信号是从 1-64：

```shell
$ kill  -l  # 查看系统中所以的信号

1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
 6) SIGABRT	 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
63) SIGRTMAX-1	64) SIGRTMAX
```



**2、信号处理的方式**：忽略，捕捉，默认动作

**忽略信号**：大多数信号可以使用这个方式来处理，但是有两种信号不能被忽略（分别是 `SIGKILL`和`SIGSTOP`）。因为他们向内核和超级用户提供了进程终止和停止的可靠方法，如果忽略了，那么这个进程就变成了没人能管理的的进程，显然是内核设计者不希望看到的场景。

**捕捉信号**：需要告诉内核，用户希望如何处理某一种信号，说白了就是写一个信号处理函数，然后将这个函数告诉内核。当该信号产生时，由内核来调用用户自定义的函数，以此来实现某种信号的处理。

**系统默认动作**：对于每个信号来说，系统都对应由默认的处理动作，当发生了该信号，系统会自动执行。不过，对系统来说，**大部分**的处理方式都比较粗暴，就是直接杀死该进程。具体的信号默认动作可以使用`man 7 signal`来查看系统的具体定义。在此，我就不详细展开了，需要查看的，可以自行查看。也可以参考 《UNIX 环境高级编程（第三部）》的 P251——P256中间对于每个信号有详细的说明。

**3、使用信号**

```shell
# 使用消息队列的代码演示
# 运行程序
$./get
key = 29536


# 查找程序的pid
$ ps  -aux|grep get
wflin      1891  0.0  0.3 1860204 13636 ?       Sl   09:29   0:16 /usr/bin/pulseaudio --start --log-target=syslog
wflin     29536  0.0  0.0   4512   804 pts/0    S+   15:44   0:00 ./get
wflin     29540  0.0  0.0  16184  1076 pts/1    S+   15:44   0:00 grep --color=auto get

# 杀死程序(9的原因是信号中 SGKILL 的代号是 9 ，代指杀死信号,kill 指令也是可以用来向系统发送信号，见 signalDemo2.c )
$ kill  -9  29536

# get 程序的执行结果是
killed 
```

### 信号处理函数

**入门版本**：函数   **signal**

**高级版本**：函数    **sigaction**

#### **入门版本编程实战：**

```c
// 无返回值的指针函数，传入一个 int 型变量 
typedef void (*sighandler_t)(int);

// 第一个参数是信号类型，第二个参数是
sighandler_t signal(int signum, sighandler_t handler);

```

* 样例程序 ctrl + c 杀不死进程  (1) 捕捉信号之后改默认

  ```c
  // 模拟键盘按下ctrl + c 无法停止进程
  
  #include <signal.h>
  #include <stdio.h>
  
  // typedef void (*sighandler_t)(int);
  
  // sighandler_t signal(int signum, sighandler_t handler);
  
  // 修改默认的处理函数，也就是如果按ctrl+c 就执行handler函数不结束。
  void handler (int signum){
  	printf("get signum = %d\n",signum);
  	switch(signum){
  		case 2:
  			printf("SIGINT\n");
  			break;
  		case 9:
  			printf("SIGKILL\n");
  			break;
  		case 10:
  			printf("SIGUSR1\n");
  			break;
  	}
  	printf("never quit\n");
  }
  
  int main(){
  	signal(SIGINT,handler);	//信号注册
  	signal(SIGKILL,handler);
  	signal(SIGUSR1,handler);
  	while(1);
  	return 0;
  ```

* 样例程序 ctrl + c 杀不死进程  (1) 忽略 ctl+c 的信号

  ```c
  #include <signal.h>
  #include <stdio.h>
  int main(){
  
         signal(SIGKILL,SIG_IGN); // 杀死依然无法忽略
         signal(SIGINT,SIG_IGN);
         while(1);
         return 0;
  }
  ```

#### **高级版本实战**

**常用api**

```c
#include <signal.h>

// 参数说明 signum 信号值，第一个 sigaction 绑定消息和参数，第二个sigaction 备份原有的信号操作，如果不需要传入NULL
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

struct sigaction {
   void       (*sa_handler)(int); //信号处理程序，不接受额外数据，SIG_IGN 为忽略，SIG_DFL 为默认动作
   void       (*sa_sigaction)(int, siginfo_t *, void *); //信号处理程序，能够接受额外数据和sigqueue配合使用
   sigset_t   sa_mask;//阻塞关键字的信号集，可以再调用捕捉函数之前，把信号添加到信号阻塞字，信号捕捉函数返回之前恢复为原先的值。
   int        sa_flags;//影响信号的行为SA_SIGINFO表示能够接受数据
 };
//回调函数句柄sa_handler、sa_sigaction只能任选其一

// siginfo 结构体携带的是信号的了内容,xxx_t 意思就是一个结构体
//主要有：
           siginfo_t {
               int      si_signo;     /* Signal number */
               int      si_errno;     /* An errno value */
               int      si_code;      /* Signal code */
               int      si_trapno;    /* Trap number that caused
                                         hardware-generated signal
                                         (unused on most architectures) */
               pid_t    si_pid;       /* Sending process ID */
               uid_t    si_uid;       /* Real user ID of sending process */
               int      si_status;    /* Exit value or signal */
               clock_t  si_utime;     /* User time consumed */
               clock_t  si_stime;     /* System time consumed */
               sigval_t si_value;     /* Signal value */
               int      si_int;       /* POSIX.1b signal */
               void    *si_ptr;       /* POSIX.1b signal */
               int      si_overrun;   /* Timer overrun count;
                                         POSIX.1b timers */
               int      si_timerid;   /* Timer ID; POSIX.1b timers */
               void    *si_addr;      /* Memory location which caused fault */
               long     si_band;      /* Band event (was int in
                                         glibc 2.3.2 and earlier) */
               int      si_fd;        /* File descriptor */
               short    si_addr_lsb;  /* Least significant bit of address
                                         (since Linux 2.6.32) */
               void    *si_lower;     /* Lower bound when address violation
                                         occurred (since Linux 3.19) */
               void    *si_upper;     /* Upper bound when address violation
                                         occurred (since Linux 3.19) */
               int      si_pkey;      /* Protection key on PTE that caused
                                         fault (since Linux 4.6) */
               void    *si_call_addr; /* Address of system call instruction
                                         (since Linux 3.5) */
               int      si_syscall;   /* Number of attempted system call
                                         (since Linux 3.5) */
               unsigned int si_arch;  /* Architecture of attempted system call
                                         (since Linux 3.5) */
           }
```
