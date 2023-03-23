/**
 * Esempio di generazione dei thread mediante libreria Pthread
 * 
 * Revisione del codice di esempio per la creazione di un thread con la
 * libreria Pthreads. Gestita l'eventualità di parametro mancante da
 * riga di comando e passaggio di una variabile di tipo intero.
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

int sum;                   /* Questo dato è condiviso dai thread */
void *runner(void *param); /* Funzione richiamata dai thread */

int main(int argc, char *argv[])
{
    int val;

    pthread_t tid;
    pthread_attr_t attr;

    /* Imposta gli attributi predefiniti del thread */
    pthread_attr_init(&attr);
    /* Crea il thread */

    /* Controllo definito parametro in ingresso*/
    if (argc < 2)
    {
        val = 10;
    }
    else
    {
        val = atoi(argv[1]);
    }

    pthread_create(&tid, &attr, runner, &val);
    /* Attende la terminazione del thread */
    pthread_join(tid, NULL);

    printf("Calcolo completato, sum = %d\n", sum);
}

/* Il thread viene eseguito in questa funzione */
void *runner(void *param)
{
    int i, upper = *((int *)param);
    sum = 0;

    for (i = 1; i <= upper; i++)
    {
        sum += i;
    }

    pthread_exit(0);
}