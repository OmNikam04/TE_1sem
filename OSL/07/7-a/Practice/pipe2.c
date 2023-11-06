#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
extern int errno;


int main(){

    //todo: create the fifo with same name
    int ret = mkfifo("/tmp/myfifo", 0777);
    if(ret<0 && errno!=EEXIST){
        printf("Error while creating fifo2..\n");
        exit(1);
    }


    //todo: wait for input from fifo1
    printf("Waiting for data from fifo1...\n");
    sleep(5);

    //todo: Open the fifo and read the input 
    int fd1 = open("/tmp/myfifo", O_RDONLY);
    char readSentence[500];
    read(fd1, readSentence, 500);
    printf("Senetence from fifo 1: %s\n", readSentence);

    return 0;
}