/**
 * Esempio di race condition nei thread generati mediante libreria Pthread
 *
 * Esempio di generazione di più thread per la gestione di un compito
 * e attesa del completamento di tutti i thread. L'esempio utilizza la
 * libreria Pthreads.
 *
 * Riferimento alle slide
 * File: SODTR_05_Thread [I Thread]
 * Slide: Pthreads esempio [#29]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <pthread.h>
#include <stdio.h>

// #include <semaphore.h>
// #include <fcntl.h>

#include <sys/time.h>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>

#define ELAPSED(end, start) (double)((end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000)) / 1000

#ifndef LOCAL_MUTEX
#define USE_MUTEX true
#endif

#define NUM_THREADS 5

int sum;                   /* Questo dato è condiviso dai thread */
void *runner(void *param); /* Funzione richiamata dai thread */

#if USE_MUTEX == true
pthread_mutex_t mutex;
#endif

/* Struttura dati per parametri in ingresso alla funzione richiamata dai thread */
struct threadData
{
    uint start;
    uint end;
};

int main(int argc, char *argv[])
{
    struct timeval start,
        end;

#if USE_MUTEX == true
    pthread_mutex_init(&mutex, NULL);
#endif

    int val;

    threadData data[NUM_THREADS];
    pthread_t tid[NUM_THREADS];

    pthread_attr_t attr;
    // pthread_attr_t attr[NUM_THREADS];

    /* Imposta gli attributi predefiniti del thread */
    pthread_attr_init(&attr);

    gettimeofday(&start, NULL);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        data[i].start = i * NUM_THREADS + 1;
        data[i].end = data[i].start + NUM_THREADS;

        /* Crea il thread */
        pthread_create(&tid[i], &attr, runner, &data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        /* Attende la terminazione del thread */
        pthread_join(tid[i], NULL);
    }
    printf("Calcolo completato, sum = %d\n", sum);

    gettimeofday(&end, NULL);

    printf("Tempo di esecuzione: %.3f\n", ELAPSED(end, start));
}

/* Il thread viene eseguito in questa funzione */
void *runner(void *param)
{
    threadData data = *((threadData *)param);

    printf("Thread %d avviato. Eseguo il calcolo da %d a %d.\n", gettid(), data.start, data.end - 1);

#if USE_MUTEX == true
    pthread_mutex_lock(&mutex);

    printf("Mutex acquisito dal thread %d.\n", gettid());
#endif

    int lsum = sum;

    for (int i = data.start; i < data.end; i++)
    {
        lsum += i;
    }

    usleep(100e3);

    sum = lsum;

#if USE_MUTEX == true
    printf("Mutex rilasciato dal thread %d.\n", gettid());

    pthread_mutex_unlock(&mutex);
#endif

    pthread_exit(0);
}