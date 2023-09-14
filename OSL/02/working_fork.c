#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>


int main(){

	fork();
	printf("This is process with fork %d\t\n", getpid());
	return 0;
}