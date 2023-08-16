#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void sort_change(char *start, char *end)
{
    int len = end - start;
    char ch;
    int i = 0;
    printf("len = %d\n", len);
    
    for (; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (start[i] > start[j])
            {
                ch = start[i];
                start[i] = start[j];
                start[j] = ch;
            }
        }
    }
    start[i] = '\0';
}

int main(int argc, const char **argv)
{
    char str[128] = "1452789End123";
    // scanf("%s", str);
    char *end = strstr(str, "End");
    sort_change(str, end);
    printf("start = %s\n", str);

    int number = atoi("12345");
    printf("number = %d\n", number);
    return 0;
}
