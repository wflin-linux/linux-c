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
		write(fd,str,strlen(str));
		sleep(2);
		if(cnt == 5){
			break;
		}
	}

	close(fd);
	return 0;
}

//  运行会阻塞