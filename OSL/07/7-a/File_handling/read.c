#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fptr;
    fptr = fopen("demo.txt", "r");
    char str[100];

    if(fptr == NULL){
        printf("Error while reading file");
        exit(1);
    }

    while(fgets(str, sizeof(str), fptr) != NULL ){
        printf("%s", str);
    }

    fclose(fptr);
    return 0;
}