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

* 