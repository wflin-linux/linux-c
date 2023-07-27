#include <stdio.h>
#include <string.h>
#include <math.h>

void test01()
{
    char msg[1024];
    sprintf(msg, "lll%s", "你好");
    printf("msg = %s\n", msg);
}

int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
