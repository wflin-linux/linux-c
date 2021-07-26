#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// int mkfifo(const char *pathname, mode_t mode);

int main(){
	int cnt = 0;
	char *str = "message from fifo"; 
	if(( mkfifo("./file",0600) == -1 )&& errno!=EEXIST){
		printf("mkfifo failuer\n");	
		perror("why");
	}
	int fd = open("./file",O_WRONLY);
	printf("write open success!\n");

	while(1){
		printf("test:send fifo :%s\n",str);
		write(fd,str,strlen(str));
		printf("please input your message you want to send:\n");
		scanf("%s",str);
		write(fd,str,strlen(str));
		read(fd,str,1000);
		printf("read byte from fifo,context:%s\n",str);
		}

	close(fd);
	return 0;
}

//  运行会阻塞