#include<stdio.h>

void f(){
	printf("f is function\n");
}
int i = 1;

int main(){
	f();
	i = 4;
	printf("hello world\n");
	return 0;
}
