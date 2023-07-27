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
