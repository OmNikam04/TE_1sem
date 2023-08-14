#include<pthread.h>
#include<stdio.h>
// passing value to function
void *compute(void *add);

int main(){
    
    pthread_t mythead1, mythread2;
    
    long value1 = 1;
    long value2 = 2;

    pthread_create(&mythead1, NULL, compute,(void*) &value1);
    pthread_create(&mythread2, NULL, compute,(void*) &value2);
    pthread_join(mythead1, NULL);
    pthread_join(mythread2, NULL);
    return 0;
}

void *compute(void *add){
    long *add_num = (long *)(add);
    printf("Add: %ld\n", *add_num);
    return NULL;
}


