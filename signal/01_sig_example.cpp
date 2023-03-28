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

int main()
{
    pid_t luke;

    // Generazione di un nuovo processo figlio.
    // Il PID verrà assegnato alla variabile luke
    luke = fork();

    if (luke == 0)
    {
        pid_t vader;

        vader = getppid();

        SPLIT(100, '=');
        // La variabile nel processo figlio non è settata
        cout << "Io sono il figlio e il mio PID è " << getpid() << endl;
        cout << "Il PID di mio padre è " << vader << endl;
        SPLIT(100, '=');

        sleep(1);

        int loop = 0;

        // Il processo figlio resterà bloccato nel loop infinito
        while (true)
        {
            cout << "Iterazione n° " << ++loop << endl;
            usleep(500e3);
        }

        // Questa riga non verrà mai stampata, in quanto il processo sarà
        // terminato alla ricezione del segnale.
        cout << "Sono uscito dal loop infinito!" << endl;
        exit(0);
    }
    else
    {
        char buffer[100];

        usleep(500e3);

        SPLIT(100, '-');
        cout << "IO SONO TUO PADRE!!!" << endl;
        sprintf(buffer, "ps -e | (head -n 1; grep %d)", luke);
        system(buffer);
        SPLIT(100, '-');

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
        kill(luke, SIGTERM);

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