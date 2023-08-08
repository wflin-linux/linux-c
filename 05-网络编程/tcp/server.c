#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 4321
#define BUFF_SIZE 1024
#define MAX_QUE_CONN_NM 5

int main()
{
    struct sockaddr_in server_sockaddr, client_sockaddr;
    int sin_size, recvbytes;
    int sockfd, client_fd;
    char buf[BUFF_SIZE];

    /*建立socket连接*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    printf("socket fd = %d\n", sockfd);

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_sockaddr.sin_zero), 0, 8);

    int i = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
    if (bind(sockfd, (struct sockaddr *)&server_sockaddr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    printf("Bind success!\n");

    if (listen(sockfd, MAX_QUE_CONN_NM) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("Listening.....\n");

    if ((client_fd = accept(sockfd, (struct sockaddr *)&client_sockaddr, (socklen_t *)&sin_size)) == -1)
    {
        perror("accept");
        exit(1);
    }

    memset(buf, 0, sizeof(buf));
    if ((recvbytes = recv(client_fd, buf, BUFF_SIZE, 0)) == -1)
    {
        perror("recv");
        exit(1);
    }
    printf("Recv : %s\n", buf);
    close(sockfd);
    exit(0);
}