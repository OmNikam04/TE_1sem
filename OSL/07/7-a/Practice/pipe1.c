#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>

#define size 100
int main(){
    //todo: Create a fifo pipe
    printf("Creating fifo pipe\n");
    mkfifo("/tmp/myfifo", 0666);
    //todo: Take input from user from terminal
    printf("Enter sentence: \n");
    char sentence[size];
    fgets(sentence, size, stdin);
    printf("Writing into fifo1...\n");

    //todo: Open fifo in write mode and write sentence in it
    int fd1 = open("/tmp/myfifo", O_WRONLY);
    write(fd1, sentence, strlen(sentence)+1);
    printf("Waiting for output from fifo2...\n");
    sleep(5);


    //todo: Read the sentence from fifo
    int fd2 = open("/tmp/myfifo", O_RDONLY);
    char readSentence[size+200];
    read(fd2, readSentence, size+200);
    printf("Output from fifo2: \n");
    printf("%s\n", readSentence);


    unlink("/tmp/myfifo");

    return 0;
}