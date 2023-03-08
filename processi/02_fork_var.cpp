/**
 * Creazione di un processo figlio mediante la chiamata fork().
 * In questo esempio il processo padre e il processo figlio condivideranno
 * lo stesso codice.
 * 
 * Il figlio modificherà il valore della variabile ship definita dal padre
 * prima della chiamata fork(). Essendo lo spazio di memoria duplicato la modifica
 * avverrà solo a livello del processo figlio.
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
#include <wait.h>
using namespace std;

string ship = "TIE Fighter";

int main()
{
    pid_t luke;

    // Generazione di un nuovo processo figlio.
    // Il PID verrà assegnato alla variabile luke
    luke = fork();

    if (luke == 0)
    {
        // Processo figlio
        cout << "Inserisci il nome della tua astronave..." << endl;
        cin >> ship;
    }
    else
    {
        // Il processo padre attende il completamento del figlio
        wait(NULL);
        cout << "La mia astronave è: " << ship << endl;
    }

    return 0;
}