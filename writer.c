#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <semaphore.h>

int GLOBAL = 10;
int readcount = 0, writercount = 0;

sem_t mutex3, mutex1, mutex2;
sem_t read, wrt;

void *reader(void * t) {
    int temp;
    temp = (int) t;
    sem_wait(&mutex3);
    sem_wait(&read);
    sem_wait(&mutex1);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&mutex1);
    sem_post(&read);
    sem_post(&mutex3);
    
    printf("The data read by the reader_no. %d is %d\n", temp, GLOBAL);
    
    sem_wait(&mutex1);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex1);
}

void *writer(void *t) {
    int temp; 
    temp = (int) t;
    sem_wait(&mutex2);
    writercount++;
    if (writercount == 1)
        sem_wait(&read);
    sem_post(&mutex2);

    sem_wait(&wrt);
    GLOBAL++;
    printf("The data written by writer_no. %d is %d\n", temp, GLOBAL);
    sem_post(&wrt);

    sem_wait(&mutex2);
    writercount--;
    if (writercount == 0)
        sem_post(&read);
    sem_post(&mutex2);
}

int main(int argc, char ** argv) {
    int i, iret_r[5], iret_w[5];
    pthread_t reade[5], write[5];

    
    sem_init(&wrt, 0, 1);
    sem_init(&read, 0, 1);
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);
    sem_init(&mutex3, 0, 1);

    for (i = 0; i < 5; i++) {
        iret_r[i] = pthread_create(&reade[i], NULL, reader, (void *)i);
        iret_w[i] = pthread_create(&write[i], NULL, writer, (void *)i);
    }
    for (i = 0; i < 5; i++) {
        pthread_join(reade[i], NULL);
        pthread_join(write[i], NULL);
    }

    return 0;
}
