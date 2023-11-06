#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>


int main()
{
    int n1 = mkfifo("pipe3",0777);
    int n2 = mkfifo("pipe4",0777);
    printf("%d\t%d\n", n1, n2);

   printf("Creating 2 pipes\n");
   unlink("pipe1");
   unlink("pipe2");

}