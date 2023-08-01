#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

int main() {
    // 创建一个 JSON 对象
    cJSON *root = cJSON_CreateObject();

    // 向 JSON 对象中添加键值对
    cJSON_AddStringToObject(root, "name", "John");
    cJSON_AddNumberToObject(root, "age", 30);
    cJSON *address = cJSON_CreateObject();
    cJSON_AddStringToObject(address, "city", "New York");
    cJSON_AddStringToObject(address, "country", "USA");
    cJSON_AddItemToObject(root, "address", address);

    // 将 JSON 对象转换成字符串
    char *json_str = cJSON_Print(root);

    // 打印 JSON 字符串
    printf("JSON String: %s\n", json_str);

    // 解析 JSON 字符串
    cJSON *parsed_root = cJSON_Parse(json_str);

    // 从解析的 JSON 对象中获取键值对
    const char *name = cJSON_GetObjectItem(parsed_root, "name")->valuestring;
    int age = cJSON_GetObjectItem(parsed_root, "age")->valueint;
    cJSON *parsed_address = cJSON_GetObjectItem(parsed_root, "address");
    const char *city = cJSON_GetObjectItem(parsed_address, "city")->valuestring;
    const char *country = cJSON_GetObjectItem(parsed_address, "country")->valuestring;

    // 打印解析后的结果
    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
    printf("City: %s\n", city);
    printf("Country: %s\n", country);

    // 释放内存
    cJSON_Delete(root);
    cJSON_Delete(parsed_root);
    free(json_str);

    return 0;
}