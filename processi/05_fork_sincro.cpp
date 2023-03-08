/**
 * Creazione di un processo figlio mediante la chiamata fork().
 * In questo esempio il processo padre e il processo figlio condivideranno
 * lo stesso codice.
 * Il processo padre attende la terminazione del processo figlio mediante la
 * chiamata wait(). Per maggiorni informazioni da cli 'man wait'.
 * 
 * Riferimento alle slide
 * File: SODTR_03_Processi [I Processi]
 * Slide: Attesa della terminazione del figlio in UNIX [#31]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <iostream>
#include <unistd.h>
#include <wait.h>
using namespace std;

void print(const char *str)
{
    while (*str != '\0')
    {
        cout << *str++ << flush;
        usleep(9);
    }
}

int main()
{
    pid_t luke;

    // Generazione di un nuovo processo figlio.
    // Il PID verrà assegnato alla variabile luke
    luke = fork();

    if (luke == 0)
    {
        // Processo figlio
        print("***************");
    }
    else
    {
        // Il processo padre attende il completamento del figlio
        wait(NULL);
        // Poi invoca la funzione per la stampa della stringa
        print("###############");
    }

    return 0;
}