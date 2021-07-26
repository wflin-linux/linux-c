#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


// int mkfifo(const char *pathname, mode_t mode);

int main(){
	char buff[1024]={0};
	int nread = 0;
	if(( mkfifo("./file",0600) == -1 )&& errno!=EEXIST){
		printf("mkfifo failuer\n");	
		perror("why");
	}
	int fd = open("./file",O_RDONLY);		//阻塞的方式运行(默认)
	// int fd = open("./file",O_RDONLY|O_NONBLOCK);		//非阻塞的方式运行,运行之后立马执行不会等待
	printf("open success!\n");

	while(1){
		int nread = read(fd,buff,30);
		printf("read %d byte from fifo,context:%s\n",nread,buff);
	}
	
	close(fd);
	return 0;
}
