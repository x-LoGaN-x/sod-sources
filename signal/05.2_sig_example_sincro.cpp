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

/**
 * @brief Funzione per la gestione personalizzata dei segnali
 *
 * @param sig Segnale ricevuto dal processo
 * @param info Puntatore alla struttura siginfo_t che contiene informazioni aggiuntive sul segnale.
 *             Per maggiori info man sigaction.
 * @param extra Puntatore a una struttura ucontext_t catato a void. La struttura contiene informazioni
 *              sul contesto del segnale che sono state salvate dal kernel sulla pila dello spazio utente
 *              (man 2 sigreturn). Per maggiori info sulla struttura man 3 getcontext e man 7 signal.l(7).
 */
void usrSignalHandler(int sig);
// bool stop = false;

int main()
{
    pid_t luke;

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
    struct sigaction usrSig;

    /* Set della funzione custom da utilizzare per la gestione dei segnali */
    usrSig.sa_handler = usrSignalHandler;

    /* Inizializzazione della maschera di segnali */
    sigemptyset(&usrSig.sa_mask);

    /**
     * Per utilizzare il gestore con tre argomenti va impostato il flag a SA_SIGINFO.
     * In questo caso, si deve impostare sa_sigaction invece di sa_handler.
     */
    usrSig.sa_flags = 0;

    /**
     * Modifica dell'azione associata ad un segnale
     *
     * int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
     *
     * La chiamata di sistema sigaction() viene utilizzata per modificare l'azione intrapresa da
     * un processo al ricevimento di un segnale specifico. Per una panoramica sui segnali,
     * vedere man 7 signal.
     *
     * signum specifica il segnale e può essere qualsiasi segnale valido, tranne SIGKILL e SIGSTOP.
     *
     * Se act è non-NULL, la nuova azione per il segnale signum viene installata da act.
     *
     * Se oldact è non-NULL, l'azione precedente viene salvata in oldact.
     *
     * Maggiori info man 2 sigaction
     */
    sigaction(SIGFPE, &usrSig, NULL);

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

void usrSignalHandler(int sig)
{
    if (sig == SIGFPE)
    {
        SPLIT(100, '#');
        cout << "Ahia... Non hai ancora imparato che non si possono fare le divisioni intere per 0? 🤬" << endl;
        SPLIT(100, '#');

        exit(-1);
    }
    else
    {
        SPLIT(100, '+');
        cout << "Ricevuto il segnale " << sig << endl;
        SPLIT(100, '+');
    }
}