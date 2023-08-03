#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
#include <time.h>

char *get_number()
{
    char *res;  // 定义一个字符串指针用于接收json格式的字符串
    double num; // 定义一个数字
    cJSON *root;

    srand(time(NULL));               // 产生一个随机数池，可以使用man手册查看该函数
    num = (rand() % 10) / 10.0 + 30; // 从随机数池中取随机数，并设置范围是30.0~39.9

    root = cJSON_CreateObject(); // 创建一个JSON对象
    if (root == NULL)
    { // 进行出错处理
        goto end;
    }

    cJSON_AddItemToObject(root, "temperature", cJSON_CreateNumber(num)); // 里面的函数是将num添加到键temperature上，
    // 外面的函数是键键值对（temperature：num）添加到JSON对象root上

    // 打印JSON对象root字符串到res中
    res = cJSON_Print(root); // 这里的res是在对空间上，因为我们经过函数处理后要保留这个值，所以最后是要释放掉这个空间的
end:
    cJSON_Delete(root); // 删除JSON对象
    return res;         // 返回结果字符串
}
int main()
{
    char *result;

    result = get_number(); // 调用函数，获取这个随机数

    printf("Content-Type:text/html;charset=utf-8\r\n");
    printf("\r\n"); // http协议请求格式，这样浏览器才能解析出这条信息。

    printf("%s\n", result);

    free(result); // 释放掉这个空间。

    return 0;
}