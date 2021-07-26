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

