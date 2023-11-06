#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void *writer_thr(void *temp);
void *reader_thr(void *temp);
sem_t mutex;
sem_t wrt;
int readcount = 0, nwt, nrd;

int main() {
    long int i;
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    pthread_t reader[100], writer[100];
    printf("\nEnter number of readers: ");
    scanf("%d", &nrd);
    printf("\nEnter number of writers: ");
    scanf("%d", &nwt);

    for (i = 1; i <= nwt; i++) {
        int *writer_id = malloc(sizeof(int));
        *writer_id = i;
        pthread_create(&writer[i], NULL, writer_thr, (void *)writer_id);
    }

    for (i = 1; i <= nrd; i++) {
        int *reader_id = malloc(sizeof(int));
        *reader_id = i;
        pthread_create(&reader[i], NULL, reader_thr, (void *)reader_id);
    }

    for (i = 1; i <= nwt; i++) {
        pthread_join(writer[i], NULL);
    }

    for (i = 1; i <= nrd; i++) {
        pthread_join(reader[i], NULL);
    }

    sem_destroy(&wrt);
    sem_destroy(&mutex);

    pthread_exit(NULL); // Exit the main thread gracefully
}

void *reader_thr(void *temp) {
    int *id_ptr = (int *)temp;
    int id = *id_ptr;
    free(id_ptr);

    // 2 semaphore are used wrt and mutex
    // wrt & mutex is binary semaphore
    printf("\nReader %d is trying to enter the database for reading.", id);
    sem_wait(&mutex);// mutex value is decrement from 1 to 0
    // if mutex is 0 then it is in blocking
    readcount++;
    if (readcount == 1){
        // multiple reader should enter the database so this is important
        sem_wait(&wrt);//if one reader 
    }
    sem_post(&mutex);// increment mutex to 1 means reader is entered in db

    printf("\nReader %d is now reading in the database.", id);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0){
        // if no reader is in db then write can enter
        sem_post(&wrt);
    }
    sem_post(&mutex);

    printf("\nReader %d has left the database.\n", id);
    sleep(3);
    pthread_exit(NULL);
}

void *writer_thr(void *temp) {
    int *id_ptr = (int *)temp;
    int id = *id_ptr;
    free(id_ptr);

    printf("\nWriter %d is trying to enter the database for modifying data.", id);
    // if reader is already in database then wrt value will 0
    // then sem_wait decrement will create blocking state and writer cannot
    sem_wait(&wrt);
    printf("\nWriter %d is writing in the database.", id);
    sleep(3);
    printf("\nWriter %d is leaving the database.\n", id);
    sem_post(&wrt);// wrt will be 1 means other reader of write can use it
    pthread_exit(NULL);
}