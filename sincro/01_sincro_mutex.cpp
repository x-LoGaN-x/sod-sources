#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <ctime>

using namespace std;

#define ELAPSED(end, start) (double)((end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000)) / 1000

#ifndef LOCAL_MUTEX
#define USE_MUTEX true
#endif

#if USE_MUTEX == true
pthread_mutex_t mutex;
#endif

pthread_t tid[2];

/* Variabile condivisa*/
int counter;

void *tryThis(void *arg);

int main(void)
{
    int i = 0;
    int error;
    struct timeval start,
        end;

#if USE_MUTEX == true
    pthread_mutex_init(&mutex, NULL);
#endif

    gettimeofday(&start, NULL);
    while (i < 2)
    {
        error = pthread_create(&(tid[i]), NULL, &tryThis, NULL);
        if (error != 0)
        {
            cerr << "Impossibile creare il thread: " << strerror(error) << endl;
            perror("Details");
        }
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    gettimeofday(&end, NULL);

    printf("Tempo di esecuzione: %.3f\n", ELAPSED(end, start));

    return 0;
}

void *tryThis(void *arg)
{
#if USE_MUTEX == true
    /* Acquisizione del mutex */
    pthread_mutex_lock(&mutex);

    printf("Mutex acquisito dal thread %d.\n", gettid());
#endif
    unsigned long i = 0;
    counter += 1;
    printf("Thread %d avviato\n", counter);

    /* Simulazione elaborazione */
    for (i = 0; i < (0xFFFFFFFF); i++)
        /* DO NOTHING */;

    printf("Thread %d completato\n", counter);

#if USE_MUTEX == true
    printf("Mutex rilasciato dal thread %d.\n", gettid());

    /* Rilascio del mutex */
    pthread_mutex_unlock(&mutex);
#endif

    return NULL;
}
