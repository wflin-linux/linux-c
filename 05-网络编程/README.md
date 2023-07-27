

# 字节序

* 大端小端都叫主机字节序

## 小端

* 将低字节存放在低地址(Linux)
* 大小端是由系统决定，用户不能改变

## 大端

* 将高字节存在高地址

## 测试

```c
// 测试机器大小端
#include <stdio.h>
union DATA
{
    unsigned short data;
    unsigned char a[2];
};

int main(int argc, char const *argv[])
{
    union DATA d;
    d.data = 0x0102;

    if (d.a[0] == 0x01 && d.a[1] == 0x02)
    {
        printf("机器是大端\n");
    }
    else
    {
        printf("机器是小端\n");
    }

    return 0;
}
```

## 网络字节序

* 网络字节序是大端

所以接收和发生都需要进行转换成相应的字节序

## 转换函数

* 头文件

  > #include<arpa/inet.h>

#### 发消息(主机字节序转网络字节序)

* htons:将两个字节的主机字节序转换成网络字节序

* htons:将主机字节序的 `端口` 转换成网络字节序

  > unit16_t htons(unit16_t  hostshort)

* htonl:将主机字节序的 `ip地址` 转换成网络字节序

  > unit32_t htonl(unit32_t hostlong)

#### 收消息(网络字节序转主机字节序)

* ntohs:将网络字节序的 `端口` 转换成主机字节序

  > unit16_t ntohs(unit16_t netshort)

* ntohl:将网络字节序的 `ip地址` 转换成主机字节序

  > unit16_t ntohl(unit16_t netlong)

```c
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    unsigned short data = 0x0102;
    printf("转换结果：%x\n",htons(data));
    return 0;
}
```

## ip地址转换

### ip地址的形式

* "192.168.100.1": 点分十进制数串
* 网络的ip地址：32位 无符号整型数据

### 将十进制数串 转成 32 位无符号整型数据（默认大端）

>  int inet_pton(int af,const char *src,void *dist)

参数说明

* af：AF_INET IPV4,AF_INET6 IPV6
* src：点分十进制数串的首元素地址
* dist：转换结果

返回值

* 成功 1 ，失败其他

```c
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    char *str = "192.168.33.100";
    unsigned int addr = 0;
    //  注意最后一个参数是无符号地址
    int ret = inet_pton(AF_INET, str, (void *)&addr);
    if (ret == 1)
    {
        printf("地址转换成功：%d\n", addr);

        // 将主机地址转换成可以看懂的地址
        unsigned char *p = (unsigned char *)&addr;
        printf("地址还原后是：%d %d %d %d\n", *p, *(p + 1), *(p + 2), *(p + 3));
    }
    else
    {
        printf("地址转换失败\n");
    }

    return 0;
}
```

* 网络中用无符号的原因
  * 有符号那个范围是 0-127
  * 无符号的范围是 0-255 【可能会越界】

### 将32位无符号数据转化成点分十进制的地址

> char *inet_ntop (int af, const void *addrptr,
> 			      char *strptr, size_t len)

参数说明

* af：AF_INET IPV4,AF_INET6 IPV6

* addrptr：32位无符号整型数的地址

* strptr：点分十进制地址

* len：点分十进制的最大长度(16)

  ```markdown
  # len的宏定义
    * #define INET_ADDRSTRLEN 16  //for ipv4
    * #define INET6_ADDRSTRLEN    //for ipv6
  ```

  ```c
  #include <stdio.h>
  #include <arpa/inet.h>
  
  int main(int argc, char const *argv[])
  {
      unsigned char buf[] = {192, 168, 33, 100};
      char ip_buf[16] = "";
  
      inet_ntop(AF_INET, buf, ip_buf, 16);
      printf("ipbuf = %s\n", ip_buf);
      return 0;
  }
  ```

## 网络通信需要解决的3大问题(应用层)

* 协议，端口，IP地址
* socket 套接字是一个特殊的文件描述符，可以使用 open，write，read，close 进行网络通信
* 通过 socket 函数调用得到这个网络通信的文件描述符(套接字)

## udp

* 相比 tcp 速度稍快
* 简单的请求应答程序可以使用 udp
* 对于海量数据传输不应该使用 udp
* 广播和多播必须使用 udp udp 应用DNS(域名解析)，NFS(网络文件系统)，RTP(流媒体)等

### udp 的编程api

```c
#include<sys/socket.h>
int socket(int domain,int type,int protocol)
```

参数

* domain协议族：协议AF_INET IPV4     AF_INET6 IPV6
* type 类型：
  * SOCK_DGRAM(udp套接字)
  * SOCK_STREAM(tcp套接字)
  * SOCK_RAW(socket套接字)
* protocol协议类别：（`0`，IPPROTO，IPPROTO_UDP）
* 返回值：通信的文件描述符 (套接字)，大于0成功，小于0 失败

### ipv4结构地址

存放 ipv4 协议通信的所有地址信息

> #include<netinet/in.h>

```c
struct sockaddr_in{
    sa_family_t sin_family; //2字节 协议(AF_INET    AF_INET6)
    in_port_t sin_port; //2字节 端口
    struct in_addr sin_addr; //4字节 IP地址(32位无符号整数)
    char sin_zero[8] // 8字节 //全写0
}
```

```c
struct in_addr{
    in_addr_t s_addr; //4字节
}
```

通用地址结构体

```c
struct sockaddr{
    sa_family_t sa_family;  //2字节
    char sa_data[14];  //14 字节
}
```

### 两种地址结构使用场合

* `struct sockaddr_in` IPv4 地址结构(存放客户端，服务器的地址信息（协议，port，IP）)
* `struct sockaddr` 通用地址结构  不是存放数据 socket API 类型转换

### 发送数据(sendto)

```c
#include <sys/types.h>
#include <sys/socket.h>
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);
```

参数说明

* sockfd：通信套接字
* buf：需要发送的消息的首元素地址
* len：消息的实际长度
* flag：0 网络默认方式通信
* dest_addr：目的主机的信息（协议，port，ip地址）
* addrlen：地址结构体的长度

返回值：发送字节数

```c
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define port 8000
#define addr "192.168.10.103"

int main(int argc, char const *argv[])
{
    // 创建通信的udp套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("sockd = %d\n", sockfd);

    // udp客户端 发送消息 给服务器
    //  定义一个ipv4数组结构，存放服务器的地址信息(目的主机)
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;                               // ipv4
    server_addr.sin_port = htons(port);                             // 服务器端口
    inet_pton(AF_INET, addr, (void *)&server_addr.sin_addr.s_addr); // 服务器的IP信息
    char *msg = "hello";
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    close(sockfd);
    return 0;
}
```

