#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

int GLOBAL = 10;

sem_t wrt, mutex;
int readcount = 0;

void *writer (void * arg) {
    int temp;
    temp = (int) arg;
    //semaphore function wait()
    sem_wait(&wrt);
    GLOBAL++;
    printf ("This is occupied by writer %d and data is %d\n", temp, GLOBAL);
    //semaphore function signal()
    sem_post(&wrt);
}

void *reader (void * arg) {
    int temp;
    temp = (int) arg;
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);
    printf("This is occupied by the reader %d and data is %d\n", temp, GLOBAL);
    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex);
}

int main(int arg, char ** argv) {   
    int i, iret_r[5], iret_w[5];

    //pthead_t is a date type for the threads. This declares the thread pointer.
    pthread_t read[5], write[5];
    
    //semaphore initialize
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < 5; i++) {

    //pthread_create is used for creating new threads.
        iret_r[i] = pthread_create(&read[i], NULL, reader, (void *)i);
        iret_w[i] = pthread_create(&write[i], NULL, writer, (void *)i);
    }
    //waits for the thread to terminate 
    for (i = 0; i < 5; i++) {
        pthread_join(read[i], NULL);
        pthread_join(write[i], NULL);
    }

    return 0;
}
