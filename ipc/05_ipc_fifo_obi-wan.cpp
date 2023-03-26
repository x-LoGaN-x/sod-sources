// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    int r2d2;

    // Configurazione del path della FIFO
    char fifoPath[] = "/tmp/r2d2Fifo";

    // Creazione della FIFO mediante la chiamata mkfifo.
    // mkfifo(const char *pathname, mode_t mode)
    mkfifo(fifoPath, 0666);

    char sndMsg[80], rcvMsg[80];
    while (1)
    {
        cout << "Apertura della FIFO" << endl;
        // Apertura della FIFO in sola lettura
        r2d2 = open(fifoPath, O_RDONLY);

        // Lettura del messaggio dalla FIFO
        read(r2d2, sndMsg, sizeof(sndMsg));

        // Stampa a video del messaggio ricevuto.
        printf("Leia: %s\n", sndMsg);
        // Chiusura della FIFO
        close(r2d2);

        // Apertura della FIFO in sola scrittura
        r2d2 = open(fifoPath, O_WRONLY);

        // Richiesta del messaggio da parte dell'utente
        cout << "Inserisci il messaggio: ";
        cin.getline(rcvMsg, 80);

        // Scrittura del messaggio nella coda FIFO
        if (write(r2d2, rcvMsg, strlen(rcvMsg) + 1) == -1)
        {
            perror("Errore scrittura pipe");
            return (-1);
        }
        cout << "Prova";
        // Chiusura della FIFO
        if (close(r2d2) == -1)
        {
            perror("Errore di chiusura");
            return (-1);
        }
    }
    return 0;
}
