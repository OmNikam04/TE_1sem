#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

sem_t wrt, mutex;

int readCount = 0, nwt, nrd;


/*
    For reader
        1. Writer can only write when the readCount is zero or there are no readers waiting
        2. If the first reader executes wait(wrt) operation before the writer does, then writer gets blocked
        3. Only when the last reader exits, it calls signal(wrt) operation signaling writer to conitue
*/
void *reader_thread(void *arg){
    int *id_ptr = (int *)arg;
    int id = *id_ptr;
    free(id_ptr);

    // decrement mutex
    // read the value
    // if readcount is 1 then wrt semphore decrement
    sem_wait(&mutex);
    readCount++;
    if(readCount == 1){
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    printf("\nReader %d is now reading in the database\n", id);

    sem_wait(&mutex);
    readCount--;
    if(readCount == 0){
        // if there is no reader in db then writer can enter
        sem_post(&wrt);
    }
    sem_post(&mutex);

    printf("Reader %d has left the database.\n", id);
    pthread_exit(NULL);
}

void *writer_thread(void *arg){
    int *id_ptr = (int *)arg;
    int id = *id_ptr;
    free(id_ptr);

    sem_wait(&wrt);
    printf("\nWriter %d is writing in database..", id);
    sleep(3);
    printf("\nWriter %d is leaving the database", id);
    sem_post(&wrt);


    pthread_exit(NULL);
}

int main(){
    int i;
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    pthread_t reader[100], writer[100];

    printf("Enter number of reader: ");
    scanf("%d", &nrd);
    printf("Enter number of writers: ");
    scanf("%d", &nwt);

    for(int i =1; i<=nwt; i++){
        // create unique id for writers
        int *writer_id = malloc(sizeof(int));
        *writer_id = i;
        pthread_create(&writer[i], NULL, writer_thread, (void *) writer_id);
    }

    for(int i = 1; i<=nrd; i++){
        // create unique id for readers
        int *reader_id = malloc(sizeof(int));
        *reader_id = i;
        pthread_create(&reader[i], NULL, reader_thread, (void *)reader_id);
    }

    for(int i = 1; i<=nwt; i++){
        pthread_join(writer[i], NULL);
    }
    for(int i = 1; i<=nrd; i++){
        pthread_join(reader[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    pthread_exit(NULL);
}