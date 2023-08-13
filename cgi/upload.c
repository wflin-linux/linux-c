#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_response(const char *message)
{
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>%s</body></html>\n", message);
}

int main()
{
    printf("Content-Type: text/html\r\n\r\n");

    char *content_length_str = getenv("CONTENT_LENGTH");
    if (!content_length_str)
    {
        send_response("Error: No data received.");
        return 1;
    }

    int content_length = atoi(content_length_str);

    char *post_data = (char *)malloc(content_length + 1);
    fgets(post_data, content_length + 1, stdin);

    // Find the start of the file data in the POST request
    char *file_start = strstr(post_data, "\r\n\r\n");
    if (!file_start)
    {
        send_response("Error: Invalid POST data.");
        free(post_data);
        return 1;
    }
    // file_start += 4; // Move past the "\r\n\r\n"

    // Extract the file data from the POST request
    FILE *fp = fopen("uploaded_file.txt", "wb");
    if (!fp)
    {
        send_response("Error: Could not open file for writing.");
        free(post_data);
        return 1;
    }
    fwrite(file_start, 1, content_length - (file_start - post_data), fp);
    fclose(fp);

    free(post_data);

    send_response("File uploaded successfully.");
    return 0;
}
