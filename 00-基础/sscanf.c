#include <stdio.h>

void test01()
{
    char input[] = "Hello World!";
    char *output;

    // 使用 %[^\n] 格式和指针输出提取的字符串，包括空格
    sscanf(input, "%s", output);

    printf("Extracted string: %s\n", output);
}

int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
