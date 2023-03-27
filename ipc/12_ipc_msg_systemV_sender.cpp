#include <iostream>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;
#define RIGHTS 0644
struct msg
{
    long type;
    char text[200];
};
int main()
{
    msg buf;
    int idQueue, len;
    key_t chiave;

    // Creazione del file di appoggio
    system("touch coda.txt");

    /**
     * Creazione di una chiave System V.
     *
     * La creazione della chiave avviene mediante la funzione ftok.
     */
    if ((chiave = ftok("coda.txt", 'B')) == -1)
    {
        cerr << "Errore nella funzione ftok." << endl;
        perror("Details");
        exit(1);
    }

    cout << "La chiave vale: " << chiave << endl;

    /**
     * Generazione dell'identificatore della coda.
     *
     * int msgget(key_t key, int msgflg);
     *
     * La chiamata di sistema msgget ottiene l'identificatore della
     * coda dei messaggi per la chiave (key) data. Se il flag IPC_CREAT è
     * impostato in msgflg, la coda viene creata, se non esiste già.
     * Il parametro msgflg è utilizzato anche per assegnare i permessi
     * alla coda in fase di creazione (9 bit meno significativi)
     */
    if ((idQueue = msgget(chiave, RIGHTS | IPC_CREAT)) == -1)
    {
        cerr << "Errore nella funzione msgget" << endl;
        perror("Details");
        exit(1);
    }

    cout << "MITTENTE: pronto a inviare i messaggi." << endl;

    cout << "Immetti il testo, ^D per terminare:" << endl;

    // Definizione del tipo di messaggio
    buf.type = 1;
    while (fgets(buf.text, sizeof buf.text, stdin) != NULL)
    {
        len = strlen(buf.text);
        // Rimozione della newline se presente
        if (buf.text[len - 1] == '\n')
        {
            buf.text[len - 1] = '\0';
        }

        /**
         * Invio del messaggio
         *
         * int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
         *
         * La chiamata di sistema msgsnd viene utilizzata per inviare messaggi in una coda
         * System V. Un processo che utilizza msgsnd deve avere il permesso di scrittura per
         * la suddetta coda di messaggi.
         * La coda di messaggi è identificata dal parametro msqid della chiamata msgsnd.
         * Il parametro successivo indica il messaggio da inviare, mentre msgsz indica la
         * dimensione del campo text del messaggio.
         *
         * Maggiori info man msgsnd
         */
        if (msgsnd(idQueue, &buf, len + 1, 0) == -1)
        {
            cerr << "Errore nell'invio del messaggio (msgsnd)" << endl;
            perror("Details");
            exit(1);
        }
    }

    // Invio del messaggio close per avvisare il processo ricevente della chiusura
    // della comunicazione.
    strcpy(buf.text, "close");
    len = strlen(buf.text);
    if (msgsnd(idQueue, &buf, len + 1, 0) == -1)
    {
        cerr << "Errore nell'invio del messaggio (msgsnd)" << endl;
        perror("Details");
        exit(1);
    }

    /**
     * @brief Construct a new if object
     *
     * int msgctl(int msqid, int cmd, struct msqid_ds *buf);
     *
     * Con msgctl si possono eseguire operazioni di controllo su una coda di messaggi identificata da msqid.
     * Il parametro cmd identifica l'operazione da eseguire. Il valore di cmd può essere IPC_RMID, IPC_STAT e IPC_SET.
     * Quando cmd è IPC_RMID, la coda di messaggi viene rimossa.
     *
     * Maggiori info man msgctl
     */
    if (msgctl(idQueue, IPC_RMID, NULL) == -1)
    {
        cerr << "Errore nella richiesta di rimozione della coda (msgctl)" << endl;
        perror("Details");
        exit(1);
    }
    cout << "MITTENTE: terminata spedizione messaggi." << endl;
    return 0;
}
