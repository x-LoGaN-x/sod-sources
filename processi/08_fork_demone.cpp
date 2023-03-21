/**
 * Creazione di un demone in Linux.
 * I demoni sono processi che girano in background perché non interagiscono
 * con gli utenti, quindi non sono associati a shell o terminale (di solito
 * il nome termina con una d).
 *
 * I passi da seguire sono i seguneti:
 * 1. creare il processo (Shell -> Padre -> Figlio)
 * 2. il padre termina, quindi il figlio diventa orfano (reparenting)
 * 3. utilizzare la chiamata di sistema setsid() per creare una nuova sessione
 *    (per maggiori info man 2 setsid). In questo modo il processo chiamante
 *    diventa group leader
 * 4. settare l'ID del processo chiamante a "process group ID" e "session ID"
 * 5. chiudere "standard input", "standard output" e "standard error" del
 *    processo perché il terminale e la shell vengono disconnesse dall'applicazione
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
using namespace std;

#define SPLIT(n, char) cout << string(n, char) << endl

int main(int argc, char *argv[])
{
    pid_t pid;
    int cont, fd, maxIter;
    char buffer[100];
    if (argc < 2)
    {
        maxIter = 5;
    }
    else
    {
        maxIter = atoi(argv[1]);
        if ((maxIter <= 0) || (maxIter > 20))
        {
            maxIter = 10;
        }
    }

    pid = fork(); // genera il nuovo processo
    switch (pid)
    {
    case -1: // Errore nella generazione del nuovo processo
        cerr << "Generazione del nuovo processo fallita!" << endl;
        perror("Details:");
        exit(-1);
        break;
    case 0: // Processo figlio
        // Apertura di file temporaneo da utilizzare per scrivere le informazioni
        fd = open("/tmp/daemon.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            cerr << "Apertura del file deamon.txt fallita!" << endl;
            perror("Details");
            return 1;
        }

        SPLIT(100, '=');
        cout << "Figlio: pid " << getpid() << " ppid " << getppid() << endl;
        cout << "Figlio prima di diventare session leader..." << endl;
        sprintf(buffer, "ps -ejf | (head -n 1; grep %s)", argv[0]);
        system(buffer);
        SPLIT(100, '=');
        sleep(2);

        // Creazione della nuova sessione

        setsid();
        SPLIT(100, '=');
        cout << "Figlio dopo essere diventato session leader" << endl;
        sprintf(buffer, "ps -ejf | (head -n 1; grep %s)", argv[0]);
        system(buffer);
        SPLIT(100, '=');

        // Chiusura dei "canali" non più utilizzati
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        break;
    default: // Processo padre
        SPLIT(100, '-');
        cout << "Padre: pid " << getpid() << " ppid " << getppid() << endl;
        SPLIT(100, '-');
        sleep(1);

        SPLIT(100, '-');
        cout << "Padre: Esco!" << endl;
        SPLIT(100, '-');
        exit(0);
    }

    // Esegue una write nel file maxIter volte
    for (cont = 0; cont < maxIter; cont++)
    {
        sprintf(buffer, "Demone: pid %d ppid %d\n", getpid(), getppid());
        write(fd, buffer, strlen(buffer));
        sleep(2);
    }
    // Scrittura della riga di chiusura
    strcpy(buffer, "Fatto!\n");
    write(fd, buffer, strlen(buffer));
    
    // Questa riga non verrà mai stampata perché STDOUT è stato chiuso
    cout << "Demone: Ho finito!!!" << endl;
    close(fd);
    return 0;
}
