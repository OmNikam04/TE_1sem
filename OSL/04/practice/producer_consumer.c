#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFFERE_SIZE 5

sem_t full, empty;
pthread_mutex_t mutex;
int buffer[BUFFERE_SIZE];

int in = 0 , out = 0;

void print_buffer(){
    printf("Buffer: [");
    for(int i = 0; i<BUFFERE_SIZE; i++){
        printf("%d, ", buffer[i]);
    }
    printf("]\n");
}
void *producer(void *arg){
    int item;
    while (1)
    {
        // create a ramdom item
        item = rand() %100;


        sem_wait(&empty);// decreases the empty semaphores value by 1

        // lock the mutex
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d Produced: %d\n", in, item);
        in = (in + 1) % BUFFERE_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);// increase the value of full semaphore

        print_buffer();

        sleep(2);
    }

    // indicates the thread is completing its execution
    // its parameter is passed to 2nd parameter of pthread_join()
    pthread_exit(NULL);
}

void *consumer(void *arg){
    int item;

    while(1){
        //decreament counter of full
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer %d Consumed%d\n", out, item);
        buffer[out] = 0;
        out = (out + 1) % BUFFERE_SIZE;

        pthread_mutex_unlock(&mutex);
        //increament counter for empty
        sem_post(&empty);

        print_buffer();

        sleep(5);
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t pt, ct;

    //1st -> name of semaphore
    //2nd -> 0 for thread (semaphore is created for thread)
    //       any non zero value for process
    //3rd -> initial value of semaphore
    sem_init(&empty, 0, BUFFERE_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);


    //1st -> name of pthread
    //2nd -> attribute of thread
    //3rd -> function which thread is executing
    //4th -> arg to function
    pthread_create(&pt, NULL, producer, NULL);
    pthread_create(&ct, NULL, consumer, NULL);


    // join is used to prevent main() to end prematurely
    pthread_join(pt, NULL);// waits for producer thread to complete its execution
    pthread_join(ct, NULL);// waits for consumer thread to complete its execution

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

}




