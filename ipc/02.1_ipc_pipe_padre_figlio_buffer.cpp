/**
 * Comunicazione mediante pipe.
 *
 * La pipe semplice può essere utilizzata da più lettori e più scrittori,
 * ma generalmente viene utilizzata in un contesto uno a uno.
 * Il kernel si occupa di bufferare i messaggi nel write end non ancora letti.
 *
 * Riferimento alle slide
 * File: SODTR_04_IPC [Comunicazione tra Processi]
 * Slide: Pipe convenzionali in UNIX [#27]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;

#define SPLIT(n, char) cout << string(n, char) << endl
#define aLen(array) sizeof(array) / sizeof(array[0])

int main()
{
    pid_t leia;

    int reply, r2d2[2];

    int sendInt[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        recvInt[10];

    char sndMsg[50] = "Messaggio ricevuto!",
         rcvMsg[50] = "";

    reply = pipe(r2d2);
    if (reply == -1)
    {
        cerr << "Errore nella creazione della pipe." << endl;
        perror("Details");
        return 1;
    }

    leia = fork();

    if (leia < 0) // Errore nella creazione del processo
    {
        cerr << "IT'S A TRAP!!! Errore nella creazione del processo figlio!" << endl;
        perror("Details");
        exit(-1);
    }
    else if (leia == 0) // Processo figlio
    {
        /**
         * Scrittura di un singolo elemento dell'array alla volta.
         *
         * Il processo padre, durante queste scritture è in sleep. Il kernel
         * eseguirà il buffer dei dati.
         */
        SPLIT(100, '-');
        for (int i = 0; i < aLen(sendInt); i++)
        {
            cout << "Leia: invio sulla pipe l'intero: " << sendInt[i] << endl;
            if (write(r2d2[1], &sendInt[i], sizeof(sendInt[i])) == -1)
            {
                cerr << "Errore invio dati nella pipe" << endl;
                perror("Details");
            }
        }
        SPLIT(100, '-');

        // Attesa per permettere al padre di leggere i dati nella pipe
        sleep(3);

        // Lettura del messaggio di chiusura proveniente dal processo padre
        SPLIT(100, '-');
        read(r2d2[0], rcvMsg, sizeof(rcvMsg));
        cout << "Leia: ricezione dalla pipe del messaggio: " << rcvMsg << endl;
        SPLIT(100, '-');
    }
    else // Processo padre
    {
        // Attesa per lasciare il tempo al processo figlio di scrivere nella pipe
        sleep(1);

        /**
         * Lettura di un singolo elemento dell'array alla volta.
         *
         * Il processo figlio ha scritto 10 elementi all'interno della pipe.
         * Il processo padre legge gli elementi uno alla volta.
         */
        SPLIT(100, '=');
        for (int i = 0; i < 10; i++)
        {
            // read(r2d2[0], recvMsg, sizeof(recvMsg));
            cout << "Byte letti: " << read(r2d2[0], &recvInt[i], sizeof(recvInt[i])) << endl;
            cout << "Obi-Wan: ricezione dalla pipe dell'intero: " << recvInt[i] << endl;
        }

        // Invio del messaggio di chiusura al processo figlio
        cout << "Obi-Wan: invio sulla pipe del messaggio: " << sndMsg << endl;
        write(r2d2[1], sndMsg, sizeof(sndMsg));
        SPLIT(100, '=');

        // Attesa del processo figlio
        wait(NULL);
    }

    return 0;
}