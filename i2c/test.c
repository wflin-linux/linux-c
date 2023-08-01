#include<stdio.h>
void display(char data){
	printf("data = %c\n",data);
}
int main(){
	printf("woshinidaye\n");
	char *buf = "woshinidaye";
	display(*buf);
	return 0;
}
