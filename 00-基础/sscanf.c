#include <stdio.h>

void test01()
{
    char input[] = "Hello World!";
    char output[128];

    // 使用 %[^\n] 格式和指针输出提取的字符串，包括空格
    sscanf(input, "%s", output);

    printf("test1 string: %s\n", output);
}

void test02()
{
    char input[] = "Hello World!";
    char output[128];

    // 使用 %[^\n] 格式和指针输出提取的字符串，包括空格
    sscanf(input, "%*s %s", output);

    printf("test2 string: %s\n", output);
}

void test03()
{
    char input[] = "123 World!";
    char output[128];
    int number;

    // 使用 %[^\n] 格式和指针输出提取的字符串，包括空格
    sscanf(input, "%d %s", &number, output);

    printf("test3 string: number=%d output=%s\n", number, output);
}

void test04()
{
    char input[] = "12345678";
    char output[128];
    // 使用 %[^\n] 格式和指针输出提取的字符串，包括空格
    sscanf(input, "%3s", output);

    printf("test4 string: output=%s\n", output);
}

void test05()
{
    int number;       // 34
    char output[128]; // 67
    char input[] = "12345678";
    // 使用 %[^\n] 格式和指针输出提取的字符串，包括空格
    sscanf(input, "%*2d%2d%*c%2s", &number, output);

    printf("test5 string: number=%d output=%s\n", number, output);
}
void test06()
{
    char output[128];
    char input[] = "ab6AB";
    // 使用 %[^\n] 格式和指针输出提取的字符串，包括空格
    sscanf(input, "%[a-z]", output);

    printf("test6 string: output=%s\n", output);
}
void test07()
{
    char output[128];
    char input[] = "123ab6AB";
    // 使用 %[^\n] 格式和指针输出提取的字符串，包括空格
    sscanf(input, "%[a-z]", output);

    printf("test7 string: output=%s\n", output);
}

void test08()
{
    char output[128];
    char input[] = "123ab6AB";
    // 使用 %[^\n] 格式和指针输出提取的字符串，包括空格
    sscanf(input, "%[0-9,a-z]", output);

    printf("test8 string: output=%s\n", output);
}

int main(int argc, char const *argv[])
{
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    test07();
    test08();
    return 0;
}
