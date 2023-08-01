#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

#define port 8000
#define addr "192.168.100.1"

int main(int argc, char const *argv[])
{
    // 创建通信的udp套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("sockd = %d\n", sockfd);

    // 定义一个ipv4 的地址结构，存放本机信息
    struct sockaddr_in my_addr;

    // 这个函数也可以清空数据
    bzero(&my_addr, sizeof(my_addr));
    // 给udp 套接字绑定一个固定的地址信息
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(9000);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 所有的地址都可以收到
    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

    // udp客户端 发送消息 给服务器
    //  定义一个ipv4数组结构，存放服务器的地址信息(目的主机)
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;                               // ipv4
    server_addr.sin_port = htons(port);                             // 服务器端口
    inet_pton(AF_INET, addr, (void *)&server_addr.sin_addr.s_addr); // 服务器的IP信息
    char msg[128] = "hello";
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&my_addr, sizeof(my_addr));
    strcpy(msg, "world");
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    close(sockfd);
    return 0;
}
