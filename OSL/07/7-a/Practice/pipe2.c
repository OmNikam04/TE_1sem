#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>


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

    int wordCt = 1, charCt=0, lineCt = 1;
    for(int i = 0; readSentence[i]!='\0'; i++){
        if(readSentence[i] == '.' || readSentence[i] == '?' || readSentence[i] == '!')
            lineCt++;
        if(readSentence[i] == ' ')
            wordCt++;
        charCt++;
    }


    //Todo: Create file and store the values in it
    FILE *fptr = fopen("db.txt", "w");
    fprintf(fptr, "No of chars %d\n", (charCt-1));
    fprintf(fptr, "No of words %d\n", wordCt);
    fprintf(fptr, "No of lines %d\n", lineCt);
    // fprintf(fptr, "%c", EOF);
    fclose(fptr);

    //Todo: Read the data from file
    fptr = fopen("db.txt", "r");
    char buffer[300];
    int i=0;
    while (fscanf(fptr, "%c", &buffer[i++]) != EOF)
    {
        buffer[i] = '\0';
    }
    fclose(fptr);

    //Todo: Write output to fifo
    fd1 = open("/tmp/myfifo", O_WRONLY);
    write(fd1, buffer, (strlen(buffer)+1));
    sleep(5);
    unlink("/tmp/myfifo");

    return 0;
}