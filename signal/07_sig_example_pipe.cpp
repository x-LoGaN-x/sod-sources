/*
 * User-defined pipe handling
 */
#include <signal.h> // libreria per i segnali
#include <cstring>  // string.h - per memset
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <unistd.h> // anche per _PC_PIPE_BUF
using namespace std;

#define SPLIT(n, char) cout << string(n, char) << endl

#define DIMBUFF 80

void usrSignalHandler(int sig);

int main(int argc, char *argv[])
{
    pid_t leia;

    int r2d2[2];

    if (pipe(r2d2) == -1)
    { // crea la pipe
        cerr << "Errore nella creazione della pipe" << endl;
        perror("Details");
        exit(-1);
    }

    /**
     * Struttura sigaction
     *
     * La struttura sigaction è definita come segue:
     *
     *     struct sigaction {
     *         void     (*sa_handler)(int);
     *         void     (*sa_sigaction)(int, siginfo_t *, void *);
     *         sigset_t   sa_mask;
     *         int        sa_flags;
     *         void     (*sa_restorer)(void);
     *     };
     *
     * Su alcune architetture è coinvolta un'unione: non assegnare sia a sa_handler che a sa_sigaction
     *
     * Il campo sa_restorer non è destinato all'uso applicativo. POSIX non specifica un campo
     * sa_restorer. Ulteriori dettagli sullo scopo di questo campo si trovano in man 2 sigreturn.
     *
     * sa_handler specifica l'azione da associare a signum:
     * - SIG_DFL per l'azione predefinita.
     * - SIG_IGN per ignorare il segnale.
     * - Un puntatore a una funzione di gestione del segnale. Questa funzione riceve come unico
     *   argomento il numero del segnale.
     *
     * Se SA_SIGINFO è specificato in sa_flags, sa_sigaction (invece di sa_handler) specifica la funzione
     * di gestione del segnale per signum. Questa funzione riceve tre argomenti (la vedremo nell'altro esempio).
     *
     * sa_mask specifica una maschera di segnali che devono essere bloccati (cioè aggiunti alla maschera di
     * segnali del thread in cui viene invocato il gestore di segnali) durante l'esecuzione del gestore di segnali.
     * Inoltre, il segnale che ha innescato il gestore sarà bloccato, a meno che non venga utilizzato il
     * flag SA_NODEFER.
     *
     * sa_flags specifica un insieme di flag che modificano il comportamento del segnale (vedi man 2 sigaction).
     *
     * Maggiori info man 2 sigaction
     */
    struct sigaction usrSig; // dichiara una struct di tipo sigaction

    /* Set della funzione custom da utilizzare per la gestione dei segnali */
    usrSig.sa_handler = usrSignalHandler;

    /* Inizializzazione della maschera di segnali */
    sigemptyset(&usrSig.sa_mask);

    /**
     * Per utilizzare il gestore con tre argomenti va impostato il flag a SA_SIGINFO.
     * In questo caso, si deve impostare sa_sigaction invece di sa_handler.
     */
    usrSig.sa_flags = 0;

    if (sigaction(SIGPIPE, &usrSig, NULL) == -1)
    {
        cerr << "Errore nell'installazione del gestore custom del segnale SIGPIPE" << endl;
        perror("Details");
        exit(-1);
    }

    char msg[] = "Aiutami, Obi-Wan Kenobi. Sei la mia unica speranza!";

    char rcv[DIMBUFF]; // dove il padre sistema la stringa ricevuta

    bool error = false;

    if (argc == 2)
    {
        error = atoi(argv[1]);
    }

    leia = fork();

    switch (leia)
    {
    case -1:
        cerr << "Errore nella generazione del nuovo processo" << endl;
        perror("Details");
        exit(-1);
        break;
    case 0:
        /**
         * Il figlio chiude il descrittore in lettura in quanto
         * utilizza la pipe solo per la scrittura.
         */
        close(r2d2[0]);

        for (ushort i = 0; i <= strlen(msg); i++)
        {
            if (write(r2d2[1], &msg[i], sizeof(char)) == -1)
            {
                cerr << "Errore durante la write sulla pipe" << endl;
                perror("Details");
                exit(-1);
            }
            usleep(100e3);
        }
        cout << "Fine della scrittura\n";
        close(r2d2[1]);
        break;
    default:
        /**
         * Il padre chiude il descrittore di scrittura in quanto utilizza la
         * pipe solo per le letture.
         */
        close(r2d2[1]);

        for (ushort i = 0; i < DIMBUFF; i++)
        {
            if (read(r2d2[0], &rcv[i], sizeof(char)) == -1)
            {
                cerr << "Errore durante la read sulla pipe" << endl;
                perror("Details");
                exit(-1);
            }
            else
            {
                cout << rcv[i] << flush;
            }
            if (i == 10 && error)
            {
                close(r2d2[0]);
                cout << endl;
            }

            if (rcv[i] == 0)
                break;
        }

        cout << endl;

        // close(r2d2[0]); // il padre chiude anche in lettura causando
        wait(NULL); // l'irritazione del figlio che riceve una SIGPIPE
        exit(0);
        rcv[DIMBUFF - 1] = 0;
        cout << "Io, il padre, ho ricevuto \"" << rcv << "\"\n";
        exit(0);
    }
}

void usrSignalHandler(int sig)
{
    SPLIT(100,'#');
    cerr << "Errore nella gestione della pipe" << endl;
    cout << "Ricevuto SIGPIPE n° " << sig << endl;
    SPLIT(100,'#');
    exit(0);
}