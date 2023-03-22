/**
 * Comunicazione mediante pipe.
 *
 * La pipe semplice può essere utilizzata da più lettori e più scrittori,
 * ma generalmente viene utilizzata in un contesto uno a uno.
 * Lo scrittore può chiudere il descrittore di uscita, mentre il lettore può
 * chiudere il descrittore d'ingresso.
 *
 * Riferimento alle slide
 * File: SODTR_03_Processi [I Processi]
 * Slide: Sostituzione dello spazio di memoria in UNIX [#30]
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
    int reply, fd[2];

    char sendMsg[2][20] = {"Me la canto...", "...e me la suono!"};

    char recvMsg[20];

    reply = pipe(fd);
    if (reply == -1)
    {
        cerr << "Errore nella creazione della pipe." << endl;
        perror("Details");
        return 1;
    }

    SPLIT(70, '-');
    cout << "Invio sulla pipe del 1° messaggio: " << sendMsg[0] << endl;
    write(fd[1], sendMsg[0], sizeof(sendMsg[0]));

    read(fd[0], recvMsg, sizeof(recvMsg));
    cout << "Ricezione dalla pipe del 1° messaggio: " << recvMsg << endl;
    SPLIT(70, '-');

    SPLIT(70, '=');
    cout << "Invio sulla pipe del 2° messaggio: " << sendMsg[1] << endl;
    write(fd[1], sendMsg[1], sizeof(sendMsg[1]));

    read(fd[0], recvMsg, sizeof(recvMsg));
    cout << "Ricezione della pipe dal 2° messaggio: " << recvMsg << endl;
    SPLIT(70, '=');

    return 0;
}