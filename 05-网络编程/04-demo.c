#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    unsigned char buf[] = {192, 168, 33, 100};
    char ip_buf[16] = "";

    inet_ntop(AF_INET, buf, ip_buf, 16);
    printf("ipbuf = %s\n", ip_buf);
    return 0;
}
