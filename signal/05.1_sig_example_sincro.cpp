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
#include <wait.h>
#include <string.h>
using namespace std;

#define SPLIT(n, char) cout << string(n, char) << endl

int main()
{

    int quot, ratio, num, den;
    char again[2];
    while (true)
    {
        cout << "Inserisci il valore del numeratore: ";
        cin >> num;
        cout << endl;

        cout << "Inserisci il valore del denominatore: ";
        cin >> den;
        cout << endl;

        quot = num / den;
        ratio = num % den;

        printf("Il quoziente della divisione %d/%d è %d, mentre il resto è %d.\n\n", num, den, quot, ratio);

        cout << "Vuoi eseguire una nuova divisione [s/n]?";
        cin >> again;
        cout << endl;
        if (!strcmp(again, "n"))
        {
            cout << "Alla prossima divisione!" << endl;
            break;
        }
    }

    return 0;
}