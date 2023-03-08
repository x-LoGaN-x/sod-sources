/**
 * Creazione di un processo figlio mediante la chiamata fork().
 * In questo esempio il processo padre e il processo figlio condivideranno
 * lo stesso codice.
 *
 * Riferimento alle slide
 * File: SODTR_03_Processi [I Processi]
 * Slide: Creazione di un processo in UNIX [#29]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    cout << "PID = " << getpid() << endl; // PID del processo
    cout << "PID genitore = " << getppid() << endl; // PID del processo padre

    pid_t luke;

    // Generazione di un nuovo processo figlio.
    // Il PID verrà assegnato alla variabile luke
    luke = fork();

    if (luke == 0)
    {
        // La variabile nel processo figlio non è settata
        cout << "Io sono il figlio e il mio PID è " << getpid() << endl;
        cout << "Il PID di mio padre è " << getppid() << endl;
    }
    else
    {
        // La variabile nel processo padre contiene il PID del figlio ed è <> 0
        cout << "IO SONO TUO PADRE!!! Il mio PID è " << getpid() << endl;
        cout << "Il PID di mio figlio è " << luke << endl;
    }

    return 0;
}