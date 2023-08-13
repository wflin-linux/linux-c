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

void send_json_response(int code, const char *msg, const char *data)
{
    printf("Content-Type: application/json\r\n\r\n");
    printf("{\"code\": %d, \"msg\": \"%s\", \"data\": %s}", code, msg, data);
}

int main()
{
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
                send_json_response(200, "请求成功", decoded_query);
            }
            else
            {
                send_json_response(400, "No GET data received", "null");
            }
        }
        else if (strcmp(request_method, "POST") == 0)
        {
            // 处理 POST 请求
            char *content_length_str = getenv("CONTENT_LENGTH");
            if (content_length_str)
            {
                int content_length = atoi(content_length_str);
                char *post_data = (char *)malloc(content_length + 1);
                fgets(post_data, content_length + 1, stdin);
                send_json_response(200, "请求成功", post_data);
                free(post_data);
            }
            else
            {
                send_json_response(400, "No POST data received", "null");
            }
        }
        else
        {
            send_json_response(400, "Unsupported request method", "null");
        }
    }
    else
    {
        send_json_response(400, "No request method found", "null");
    }

    return 0;
}
