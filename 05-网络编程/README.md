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