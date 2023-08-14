#include<pthread.h>
#include<stdio.h>
// execution command gcc test.c -lpthread
// time ./a.out
void *compute();
void *compute2();

int main(){
    pthread_t mythead1;
    pthread_t mythead2;

    // calling compute with thread
    // 1st parament reference of thread can be single or array
    // 2nd parament for interprocess communication
    // 3rd parament is for return type of function
    // 4th parament is for passing arguments to function i.e. in our case compute()
    // pthread_create(&mythead1, NULL, compute, NULL);
    // pthread_join(mythead1, NULL);
    // pthread_create(&mythead2, NULL, compute2, NULL);
    // pthread_join(mythead2, NULL);

    // calling compute without thread
    compute();
    compute2();

    return 0;
}

void *compute(){
    for(int i = 0; i<100000; i++){}
    printf("done from compute 1\n");
    return NULL;
}
void *compute2(){
    for(int i = 0; i<100000; i++){}
    printf("done from compute 2\n");
    return NULL;
}



