#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define port 8000
#define addr "192.168.10.103"

int main(int argc, char const *argv[])
{
    // 创建通信的udp套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("sockd = %d\n", sockfd);

    // udp客户端 发送消息 给服务器
    //  定义一个ipv4数组结构，存放服务器的地址信息(目的主机)
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;                               // ipv4
    server_addr.sin_port = htons(port);                             // 服务器端口
    inet_pton(AF_INET, addr, (void *)&server_addr.sin_addr.s_addr); // 服务器的IP信息
    char *msg = "hello";
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    close(sockfd);
    return 0;
}
