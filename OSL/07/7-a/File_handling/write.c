#include<stdio.h>
#include<stdlib.h>

int main(){
    int num;
    FILE *fptr;
    fptr = fopen("demo.txt","w");

    if(fptr == NULL){
        printf("Error while creating/opening file");
        exit(1);
    }

    printf("Enter num: ");
    scanf("%d", &num);
    // Consume the newline character from the input buffer
    while (getchar() != '\n');
    
    printf("Enter string: ");
    char str[100];
    fgets(str, sizeof(str), stdin);
    // writing num to file
    fprintf(fptr, "%d\n", num);
    fprintf(fptr, "%s", str);

    fclose(fptr);

    return 0;
}