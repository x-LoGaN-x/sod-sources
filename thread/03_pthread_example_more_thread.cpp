/**
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

#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

int sum;                   /* Questo dato è condiviso dai thread */
void *runner(void *param); /* Funzione richiamata dai thread */

/* Struttura dati per parametri in ingresso alla funzione richiamata dai thread */
struct threadData
{
    uint start;
    uint end;
};

int main(int argc, char *argv[])
{
    int val;

    threadData data[NUM_THREADS];
    pthread_t tid[NUM_THREADS];

    pthread_attr_t attr;
    // pthread_attr_t attr[NUM_THREADS];

    /* Imposta gli attributi predefiniti del thread */
    pthread_attr_init(&attr);

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
}

/* Il thread viene eseguito in questa funzione */
void *runner(void *param)
{
    threadData data = *((threadData *)param);

    printf("Thread %d avviato. Eseguo il calcolo da %d a %d.\n", gettid(), data.start, data.end - 1);

    for (int i = data.start; i < data.end; i++)
    {
        sum += i;
    }
    
    pthread_exit(0);
}