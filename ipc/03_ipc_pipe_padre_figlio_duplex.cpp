/**
 * Comunicazione mediante pipe.
 *
 * La pipe semplice può essere utilizzata da più lettori e più scrittori,
 * ma generalmente viene utilizzata in un contesto uno a uno.
 * In questo esempio si utilizzano due pipe per realizzare una comunicazione
 * full duplex.
 *
 * Riferimento alle slide
 * File: SODTR_04_IPC [Comunicazione tra Processi]
 * Slide: Pipe convenzionali in UNIX [#27]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <iostream>
#include <unistd.h>
using namespace std;

#define SPLIT(n, char) cout << string(n, char) << endl

int main()
{
    pid_t leia;

    int reply,
        r2d2[2], // Utilizzata in write dal figlio e in read dal padre
        r2q5[2]; // Utilizzata in write dal padre e in read dal figlio

    char sendMsg[2][100] = {"Aiutami, Obi-Wan Kenobi. Sei la mia unica speranza!", "Messaggio ricevuto!"};

    char recvMsg[100];

    reply = pipe(r2d2);
    if (reply == -1)
    {
        cerr << "Errore nella creazione della pipe." << endl;
        perror("Details");
        return 1;
    }

    reply = pipe(r2q5);
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
        // Chiusura delle estremità delle pipe non utilizzate
        close(r2d2[0]);
        close(r2q5[1]);
        SPLIT(100, '-');
        cout << "Leia: invio sulla pipe del messaggio: " << sendMsg[0] << endl;
        write(r2d2[1], sendMsg, sizeof(sendMsg[0]));
        SPLIT(100, '-');
        read(r2q5[0], recvMsg, sizeof(recvMsg));
        SPLIT(100, '-');
        cout << "Leia: ricezione dalla pipe del messaggio: " << recvMsg << endl;
        SPLIT(100, '-');
    }
    else
    {
        // Chiusura delle estremità delle pipe non utilizzate
        close(r2d2[1]);
        close(r2q5[0]);
        read(r2d2[0], recvMsg, sizeof(recvMsg));
        SPLIT(100, '=');
        cout << "Obi-Wan: ricezione dalla pipe del messaggio: " << recvMsg << endl;
        cout << "Obi-Wan: invio sulla pipe del messaggio: " << sendMsg[1] << endl;
        write(r2q5[1], sendMsg[1], sizeof(sendMsg[1]));
        SPLIT(100, '=');
    }

    return 0;
}