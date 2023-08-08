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
