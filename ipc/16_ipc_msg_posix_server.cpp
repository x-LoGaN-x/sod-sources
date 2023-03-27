/*
 * server.c: Server program
 *           to demonstrate interprocess commnuication
 *           with POSIX message queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include <iostream>
using namespace std;

#define ID_QUEUE_SIZE 50
#define TEXT_SIZE 50

#define SERVER_QUEUE_NAME "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE ID_QUEUE_SIZE + TEXT_SIZE
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

struct msg
{
    char idQueue[ID_QUEUE_SIZE];
    char text[TEXT_SIZE];
};

int main(int argc, char **argv)
{
    mqd_t qdServer, qdClient; // queue descriptors
    long token_number = 1;    // next token to be given to client

    printf("Server: Hello, World!\n");

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    /**
     * Apertura della coda
     *
     * mqd_t mq_open(const char *name, int oflag);
     * mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
     *
     * La funzione mq_open serve ad aprire una coda POSIX. Il primo parametro name specifica il nome della coda.
     * Il secondo parametro è un flag che può essere O_RDONLY per la ricezione di messaggi, O_WRONLY per l'invio
     * di messaggi e O_RDWR per le operazioni di invio e ricezione sulla stessa coda.
     * A questo flag possono essere aggiunti altri valori in OR, ad esempio è possibile specificare O_NONBLOCK
     * per utilizzare la coda in modalità non bloccante. Per impostazione predefinita, mq_send si blocca se la coda
     * è piena e mq_receive si blocca se non ci sono messaggi nella coda. Ma se O_NONBLOCK è specificato in oflag,
     * la chiamata ritornerà in questi casi immediatamente con errno impostato a EAGAIN.
     *
     * Se si specifica O_CREAT come parte di oflag, la coda viene creata, se non esiste già. Se si specifica O_EXCL
     * insieme a O_CREAT e la coda esiste, mq_open fallisce con errno impostato a EEXIST. Se O_CREAT è specificato
     * in oflag, si deve usare la seconda forma di mq_open con due parametri aggiuntivi.
     * In questo caso, mode specifica i permessi per la coda e il puntatore alla struct mq_attr fornisce gli
     * attributi per la coda di messaggi. Se questo puntatore è NULL, viene creata una coda con attributi predefiniti.
     *
     * Maggiori info man mq_open
     */
    if ((qdServer = mq_open(SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
    {
        cerr << "Errore nell'apertura della coda del server (mq_open)." << endl;
        perror("Details");
        exit(1);
    }

    // char inBuf[MSG_BUFFER_SIZE];
    // char outBuf[MSG_BUFFER_SIZE];

    msg inMsg, outMsg;

    while (1)
    {
        /**
         * Ricezione di un messaggio dalla coda
         *
         * ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
         *
         * mq_receive riceve un messaggio dalla coda a cui fa riferimento il descrittore mqdes. Il più
         * vecchio con la priorità più alta viene eliminato dalla coda e passato al processo nel buffer
         * puntato da msg_ptr. msg_len è la lunghezza del buffer in byte e deve essere maggiore della
         * dimensione massima del messaggio, l'attributo mq_msgsize, per la coda. Se il puntatore
         * msg_prio non è nullo, la priorità del messaggio ricevuto viene memorizzata nel numero intero
         * da esso indicato. Il comportamento predefinito di mq_receive è quello di bloccarsi se non
         * ci sono messaggi nella coda. Tuttavia, se il flag O_NONBLOCK è abilitato per la coda e la
         * coda è vuota, mq_receive ritorna immediatamente con errno impostato a EAGAIN.
         * In caso di successo, mq_receive restituisce il numero di byte ricevuti nel buffer indicato
         * da msg_ptr.
         *
         * Maggiori info man mq_receive
         */
        // if (mq_receive(qdServer, (char *)&inMsg, MSG_BUFFER_SIZE, NULL) == -1)
        if (mq_receive(qdServer, (char *)&inMsg, 1100, NULL) == -1)
        {
            cerr << "Server: Errore nella ricezione del messaggio (mq_receive)" << endl;
            perror("Details");
            exit(1);
        }

        // printf("Server: message received - %s.\n", inMsg.text);
        cout << "Server: messaggio ricevuto" << endl;
        cout << "Id coda: " << inMsg.idQueue << ", messaggio: " << inMsg.text << endl;

        // Apertura della coda del client
        if ((qdClient = mq_open(inMsg.idQueue, O_WRONLY)) == 1)
        {
            cerr << "Server: Errore nell'apertuira della coda del client" << endl;
            perror("Details");
            continue;
        }

        sprintf(outMsg.text, "%ld", token_number);

        if (mq_send(qdClient, (char *)&outMsg, sizeof(outMsg), 0) == -1)
        {
            cerr << "Server: Errore nell'invio del messaggio al client" << endl;
            perror("Details");
            continue;
        }

        cout << "Server: token inviato al client" << endl;
        token_number++;

        if (!strcmp(inMsg.text, "close"))
        {
            cout << "Server: chiusura del server in corso" << endl;
            break;
        }
    }

    /**
     * Chiusura della coda di ricezione
     *
     * int mq_close (mqd_t mqdes);
     *
     * La chiamata mq_close chiude il descrittore della coda mqdes.
     *
     * Maggiori info man mq_close
     */
    if (mq_close(qdServer) == -1)
    {
        cerr << "Server: Errore nella chiusura della coda di ricezione (mq_close)" << endl;
        perror("Details");
        exit(1);
    }

    /**
     * Rimozione della coda di ricezione
     *
     * int mq_unlink(const char *queue_name);
     *
     * mq_unlink rimuove la coda con nome queue_name.
     *
     * Maggiori info man mq_unlink
     */
    if (mq_unlink(SERVER_QUEUE_NAME) == -1)
    {
        cerr << "Server: errore nella rimozione della coda (mq_unlink)" << endl;
        perror("Details");
        exit(1);
    }
    cout << "Server: Lunga vita e prosperità! 🖖" << endl;
}
