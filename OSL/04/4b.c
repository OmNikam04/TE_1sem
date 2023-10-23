#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>


sem_t x, y;     
pthread_t tid; 

int readercount = 0; 


void *reader(void* param)
{
    while(1){
    sem_wait(&x);                    // Wait on semaphore x 
    readercount++;                
    if(readercount == 1)
    {
        sem_wait(&y); //  wait on semaphore y to block writers.
    }    
    sem_post(&x); // Leaving critical section.
    printf("%d reader inside\n", readercount); 
    usleep(3);
    sem_wait(&x); 
    readercount--; // Decrement the reader count.
    if(readercount == 0)
    {
        sem_post(&y); // Signal semaphore y to allow writers.
    }
    sem_post(&x); // Exit the critical section.
    printf("%d reader done\n", readercount + 1);
    return NULL;
}
}
void *writer(void* param)
{
    while(1){
    printf("Writer trying to enter\n"); 
    sem_wait(&y);                            // Wait on semaphore y to enter the critical section.
    printf("Writer entered\n");              
    sem_post(&y);                           // Exit the critical section.
    printf("Writer done.\n");       
    return NULL;
}
}
int main()
{
    int n;
    pthread_t wthreads[10], rthreads[10]; 
    printf("Enter the number of readers:"); 
    scanf("%d", &n); 
    printf("\n");
    int arr[n];
    sem_init(&x, 0, 1); // Initialize semaphore x value of 1.
    sem_init(&y, 0, 1); // Initialize semaphore y value of 1.
    for(int i = 0; i < n; i++)
    {
        pthread_create(&wthreads[i], NULL, reader, NULL); // Create reader threads.
        pthread_create(&rthreads[i], NULL, writer, NULL); // Create writer threads.
    }
    for(int i = 0; i < n; i++)
    {
        pthread_join(wthreads[i], NULL); // Wait for reader threads to finish.
        pthread_join(rthreads[i], NULL); // Wait for writer threads to finish.
    }

    return 0;
}