#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define DIM_BUF 1024
#define KEY 0x1234

using namespace std;
int main()
{
    char c;
    int idShmem;
    char *ptrShmem;

    /**
     * Creazione del segmento di memoria condivisa
     *
     * int shmget(key_t key, size_t size, int shmflg);
     *
     * shmget()  ritorna l'identificatore della memoria condivisa associato alla key utilizzata
     * tra gli argomenti. Può essere utilizzata per otternere l'identificatore di un segmento
     * creato in precedenza (solo se il flag shmflg e la key non ha il valore IPC_PRIVATE)
     * oppure per creare un nuovo segmento.
     *
     * Maggiori info man shmget
     */
    idShmem = shmget(KEY, DIM_BUF, 0644 | IPC_CREAT);
    if (idShmem == -1)
    {
        cerr << "Fallimento apertura memoria condivisa" << endl;
        perror("Details");
        return 1;
    }

    /**
     * Allaccio del segmento di memoria
     *
     * void *shmat(int shmid, const void *shmaddr, int shmflg);
     *
     * shmat()  "attacca" il segmento di memoria condivisa identificato da shmid all'interno
     * dello spazio degli indirizzi del processo chimante.
     *
     * Maggiori informazioni man shmat.
     */
    ptrShmem = (char *)shmat(idShmem, NULL, 0);
    if (ptrShmem == (void *)-1)
    {
        cerr << "Fallimento associatura memoria condivisa\n";
        return 1;
    }

    // Ciclo di scrittura delle lettere
    for (c = 'A'; c < 'F'; c++)
    {
        memset(ptrShmem, c, DIM_BUF - 1);
        *(ptrShmem + DIM_BUF) = '\0';
        cout << "Scrittore: lettere " << c << " scritte" << endl;
        sleep(3);
    }

    /**
     * Distacco della memoria
     *
     * int shmdt(const void *shmaddr);
     *
     * shmdt() distacca la memoria condivisa che si trova all'indirizzo specificato
     * da shmaddr dallo spazio di memoria del processo chiamante. Il valore shmaddr deve essere
     * lo stesso restituito dalla chiamata shmat in fase di "attacco".
     *
     * Maggiori info man shmdt.
     */
    cout << "Scrittore: dissocio memoria condivisa" << endl;
    if (shmdt(ptrShmem) == -1)
    {
        cerr << "Errore nel dissociare la memoria condivisa." << endl;
        perror("Details");
        return 1;
    }

    /**
     * Rilasio della memoria condivisa
     *
     * int shmctl(int shmid, int cmd, struct shmid_ds *buf);
     *
     * shmctl() esegue il comando specificato da cmd sul segmento di memoria condivisa
     * identificato da shmid.
     *
     * Maggiori info man shmctl
     */
    if (shmctl(idShmem, IPC_RMID, 0) == -1)
    {
        cerr << "Errore nel segnalare la memoria come da distruggere" << endl;
        perror("Details");
        return 1;
    }

    cout << "Scrittore: finito!" << endl;

    return 0;
}