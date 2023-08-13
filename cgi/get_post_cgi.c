#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 解码 URL 编码的字符串（将 %XX 形式转换为字符）
void url_decode(char *str, const char *input)
{
    char *p = str;
    while (*input)
    {
        if (*input == '%')
        {
            char code[3];
            code[0] = input[1];
            code[1] = input[2];
            code[2] = '\0';
            *str++ = strtol(code, NULL, 16);
            input += 3;
        }
        else if (*input == '+')
        {
            *str++ = ' ';
            input++;
        }
        else
        {
            *str++ = *input++;
        }
    }
    *str = '\0';
}

int main()
{
    printf("Content-Type: text/html\r\n\r\n");

    char *request_method = getenv("REQUEST_METHOD");

    if (request_method)
    {
        if (strcmp(request_method, "GET") == 0)
        {
            // 处理 GET 请求
            char *query_string = getenv("QUERY_STRING");
            if (query_string)
            {
                char decoded_query[100];
                url_decode(decoded_query, query_string);
                printf("Received GET data: %s\n", decoded_query);
            }
            else
            {
                printf("No GET data received.\n");
            }
        }
        else if (strcmp(request_method, "POST") == 0)
        {
            // 处理 POST 请求
            char *content_length_str = getenv("CONTENT_LENGTH");
            printf("content_length_str = %s\n", content_length_str);
            if (content_length_str)
            {
                int content_length = atoi(content_length_str);
                char *post_data = (char *)malloc(content_length + 1);
                fgets(post_data, content_length + 1, stdin);
                printf("content_length = %d\n", content_length);
                printf("Received POST data: %s\n", post_data);
                free(post_data);
            }
            else
            {
                printf("No POST data received.\n");
            }
        }
        else
        {
            printf("Unsupported request method.\n");
        }
    }
    else
    {
        printf("No request method found.\n");
    }

    return 0;
}
