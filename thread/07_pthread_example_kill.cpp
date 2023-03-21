/**
 * Esempio di invio di segnali mediante la chiamata pthread_kill.
 * L'esempio utilizza la libreria Pthreads.
 *
 * Riferimento alle slide
 * File: SODTR_05_Thread [I Thread]
 * Slide: Segnali e multithreading [#41]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

void *runner(void *param); /* Funzione richiamata dal thread */

int main(int argc, char *argv[])
{
    int status;
    int threadparm = 1;
    pthread_t tid;
    pthread_attr_t attr;
    int thread_stat;

    printf("Pid: %d, Tid: %d.\n", getpid(), gettid());

    pthread_attr_init(&attr);

    status = pthread_create(&tid,
                            &attr,
                            runner,
                            (void *)&threadparm);
    if (status < 0)
    {
        perror("pthread_create failed");
        exit(1);
    }

    sleep(5);

    cout << "Invio del segnale SIGUSR1..." << endl;

    status = pthread_kill(tid, SIGUSR1);
    if (status < 0)
        perror("pthread_kill fallita");

    status = pthread_join(tid, (void **)&thread_stat);
    if (status < 0)
        perror("pthread_join fallita");

    printf("Lo stato di uscita del thread è %d.\n", thread_stat);

    exit(0);
}

void *runner(void *param)
{
    int threadnum;
    sigset_t set;
    int sig;

    threadnum = *((int *)param);

    printf("Esecuzione del thread %d.\n", threadnum);
    printf("Pid: %d, Tid: %d\n", getpid(), gettid());

    sigemptyset(&set);
    if (sigaddset(&set, SIGUSR1) == -1)
    {
        perror("Sigaddset error");
        pthread_exit((void **)1);
    }

    printf("Attesa del segnale...\n");

    if (sigwait(&set, &sig) != SIGUSR1)
    {
        perror("Sigwait error");
        pthread_exit((void **)2);
    }

    printf("Il valore di sig è %d\n.", sig);

    pthread_exit((void **)0);
}