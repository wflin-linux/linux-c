#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    unsigned short data = 0x0102;
    printf("转换结果：%x\n",htons(data));

    return 0;
}
