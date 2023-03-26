/**
 * Comunicazione mediante named pipe o FIFO.
 *
 * La named pipe può essere utilizzata per la comunicazione tra processi che non
 * hanno nessuna relazione di parentela.
 * In uno scenario classico si ha che più processi utilizzino una named pipe per
 * effettuare scritture, mentre un processo la utilizzi in lettura.
 * Il kernel si occupa di bufferare i messaggi nel write end non ancora letti.
 *
 * Riferimento alle slide
 * File: SODTR_04_IPC [Comunicazione tra Processi]
 * Slide: Named pipe in UNIX = FIFO [#32]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
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

    /**
     * Creazione della FIFO
     *
     * int mkfifo(const char *pathname, mode_t mode);
     *
     * mkfifo() crea un file speciale FIFO utilizzando il pathname in ingresso. Il parametro mode
     * specifica i permessi della FIFO.
     *
     * Per maggiori informazioni man 3 mkfifo
     */
    mkfifo(fifoPath, 0666);

    char sndMsg[80], rcvMsg[80];
    while (1)
    {
        cout << "Apertura della FIFO" << endl;
        /**
         * Apertura della FIFO in sola scrittura
         *
         * Quando si utilizza la chiamata open in sola scrittura su una
         * FIFO, la chiamata resta bloccata fintanto che un altro processo
         * non effettua un'apertura in sola lettura sulla stessa FIFO.
         */
        r2d2 = open(fifoPath, O_WRONLY);

        // Richiesta dell'inserimento del messaggio da riga di comando
        cout << "Inserisci il messaggio: ";
        cin.getline(rcvMsg, 80);

        // Scrittura del messaggio nella coda FIFO
        write(r2d2, rcvMsg, strlen(rcvMsg) + 1);
        // Chiusura della FIFO
        close(r2d2);

        /**
         * Apertura della FIFO in sola lettura
         *
         * Quando si utilizza la chiamata open in sola lettura su una
         * FIFO, la chiamata resta bloccata fintanto che un altro processo
         * non effettua un'apertura in sola scrittura sulla stessa FIFO.
         */
        r2d2 = open(fifoPath, O_RDONLY);

        // Lettura del messaggio dalla FIFO
        read(r2d2, sndMsg, sizeof(sndMsg));

        // Stampa a video del messaggio ricevuto.
        printf("Obi-Wan: %s\n", sndMsg);
        // Chiusura della FIFO
        close(r2d2);
    }
    return 0;
}
