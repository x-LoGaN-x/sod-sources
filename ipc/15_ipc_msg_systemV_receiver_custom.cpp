#include <iostream>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;

#define RIGHTS 0644

#define SENDER_LEN 10
#define MSG_LEN 100

struct usrData
{
    int id;
    char sender[SENDER_LEN];
    char text[MSG_LEN];
};

struct msg
{
    long type;
    usrData data;
};

int main()
{
    msg buf;
    int idQueue;
    key_t key;

    /**
     * Creazione di una chiave System V.
     *
     * La creazione della chiave avviene mediante la funzione ftok.
     */
    if ((key = ftok("coda.txt", 'B')) == -1)
    {
        cerr << "Errore nella funzione ftok." << endl;
        perror("Details");
        exit(1);
    }

    cout << "La chiave vale: " << key << endl;

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
    if ((idQueue = msgget(key, RIGHTS)) == -1)
    {
        cerr << "Errore nella funzione msgget" << endl;
        perror("Details");
        exit(1);
    }

    cout << "RICEVENTE: pronto a ricevere messaggi.\n";
    for (;;)
    {
        /**
         * Ricezione del messaggio
         *
         * ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
         *
         * La chiamata di sistema msgrcv serve a ricevere messaggi dalla coda System V
         * idendificata da msqid. Il parametro msgp punta al buffer per il messaggio in
         * arrivo e msgsz specifica lo spazio massimo disponibile per il membro text del
         * messaggio. In caso di successo la funzione restituisce il numero di byte
         * effettivamente copiati nel membro text della struttura puntata da msgp.
         *
         * Maggiori info man msgrcv
         */
        if (msgrcv(idQueue, &buf, sizeof(buf), 0, 0) == -1)
        {
            cerr << "Errore nella ricezione del messaggio (msgrcv)" << endl;
            perror("Details");
            exit(1);
        }
        cout << "Msg ricevuto... " << endl
             << "Sender: " << buf.data.sender << endl
             << "id: " << buf.data.id << endl
             << "text: " << buf.data.text << endl;

        if (!strcmp(buf.data.text, "close"))
        {
            break;
        }
    }

    cout << "RICEVENTE: terminata ricezione messaggi." << endl;

    // Rimozione del file di appoggio
    system("rm coda.txt");
    return 0;
}
