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
using namespace std;

#define SPLIT(n, char) cout << string(n, char) << endl

/**
 * @brief Funzione per la gestione personalizzata dei segnali
 *
 * @param sig Segnale ricevuto mediante la chiamata kill().
 */
void usrSignalHandler(int sig, siginfo_t *info, void *extra);

/**
 * @brief Funzione per il risveglio, mediante segnale SIGALRM di un processo.
 *
 * @param pid Processo che si vuole svegliare.
 * @return int Esito della chiamata kill.
 */
int wakeUp(pid_t pid);

bool stop = false;

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
    usrSig.sa_sigaction = usrSignalHandler;

    /* Inizializzazione della maschera di segnali */
    sigemptyset(&usrSig.sa_mask);

    /* Inizializzazione dei flag */
    usrSig.sa_flags = SA_SIGINFO;

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
    sigaction(SIGALRM, &usrSig, NULL);

    // Generazione di un nuovo processo figlio.
    // Il PID verrà assegnato alla variabile luke
    luke = fork();

    if (luke == 0)
    {
        sigaction(SIGTERM, &usrSig, NULL);

        pid_t vader;

        vader = getppid();

        SPLIT(100, '=');
        // La variabile nel processo figlio non è settata
        cout << "Io sono il figlio e il mio PID è " << getpid() << endl;
        cout << "Il PID di mio padre è " << vader << endl;
        SPLIT(100, '=');

        wakeUp(vader);

        /**
         * Attesa di un segnale
         *
         * int pause(void);
         *
         * La funzione pause() fa si che il processo (o thread) chiamante "dorma" finché
         * non viene "recapitato" un segnale che termina il processo o innesca la chiamata
         * alla funzione di gestione di quel segnale.
         *
         * Maggiori info man pause
         */
        pause();

        int loop = 0;

        // Il processo figlio resterà bloccato nel loop infinito
        while (!stop)
        {
            cout << "Iterazione n° " << ++loop << endl;
            usleep(500e3);
        }

        // Questa riga non verrà mai stampata, in quanto il processo sarà
        // terminato alla ricezione del segnale.
        SPLIT(100, '=');
        cout << "Sono uscito dal loop infinito!" << endl;
        SPLIT(100, '=');
        exit(0);
    }
    else
    {
        pid_t myPid = getpid();

        sigval value;
        value.sival_ptr = &myPid;

        char buffer[100];

        cout << "Valore di sival_ptr " << *(pid_t *)value.sival_ptr << endl;

        pause();
        
        SPLIT(100, '-');
        cout << "IO SONO TUO PADRE!!!" << endl;
        sprintf(buffer, "ps -e | (head -n 1; grep %d)", luke);
        system(buffer);
        SPLIT(100, '-');

        wakeUp(luke);

        sleep(5);

        SPLIT(100, '-');
        system(buffer);
        SPLIT(100, '-');

        cout << "Invio del segnale..." << endl;

        /**
         * Invio del segnale
         *
         * int kill(pid_t pid, int sig);
         *
         * La sistem call kill() può essere utilizzata per inviare un segnale ad un processo o
         * gruppo di processi:
         * - se pid è positivo, il segnale sig verrà inviato al processo con ID specificato da pid.
         * - se pid è uguale a 0, il segnale sig verrà inviato a tutti i processi appartenenti al gruppo
         *   del processo che ha utilizzato la chiamata di sistema
         * - se pid è uguale a -1, il segnale sig sarà inviato a tutti i processi per i quali il processo
         *   chiamante ha il permesso di inviare segnali, a eccezione del processo 1 (init).
         * - se pid è minore di -1, il segnale sig sarà inviato a tutti i processi che fanno parte del
         *   gruppo con ID -pid.
         *
         * Se sig vale 0, non sarà inviato nessun segnale, ma il controllo sull'esistenza del processo
         * e sui permessi di invio di segnali verrà comunque effettuato.
         *
         * Per maggiori info man 2 kill
         */
        sigqueue(luke, SIGTERM, value);
        // kill(luke, SIGTERM);

        SPLIT(100, '-');
        system(buffer);
        SPLIT(100, '-');

        cout << "Attendo la terminazione del processo figlio." << endl;
        wait(NULL);

        SPLIT(100, '-');
        system(buffer);
        SPLIT(100, '-');
    }

    return 0;
}

void usrSignalHandler(int sig, siginfo_t *info, void *extra)
{
    if (sig == SIGALRM)
    {
        SPLIT(100, '#');
        cout << "Il mio PID è " << getpid() << endl
             << "SIGALARM ricevuto..." << endl
             << "Il processo " << info->si_value.sival_int << " mi ha svegliato ⏰!!!" << endl;
        SPLIT(100, '#');
    }
    else if (sig == SIGTERM)
    {
        SPLIT(100, '+');
        cout << "Il mio PID è " << getpid() << endl
             << "SIGTERM ricevuto..." << endl
             << "Il processo " << *(pid_t *)info->si_value.sival_ptr << " ha chiesto la mia terminazione 💀!!!" << endl;
        SPLIT(100, '+');

        stop = true;
    }
}

int wakeUp(pid_t pid)
{
    sigval value;

    value.sival_int = getpid();

    SPLIT(100, '*');
    cout << "Invio del segnale SIGALRM al processo " << pid << endl;
    SPLIT(100, '*');
    return sigqueue(pid, SIGALRM, value);
}