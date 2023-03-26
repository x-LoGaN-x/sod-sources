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
        cerr << "Errore nell'apertura della memoria condivisa" << endl;
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
    cout << "Lettore: associo la memoria condivisa..." << endl;
    ptrShmem = (char *)shmat(idShmem, NULL, 0);
    if (ptrShmem == (void *)-1)
    {
        cerr << "Errore nell'associazione della memoria condivisa" << endl;
        perror("Details");
        return 1;
    }

    // Ciclo di lettura dalla memoria
    for (c = 'A'; c < 'F'; c++)
    {
        cout << "Lettore: leggo le " << c << endl;
        cout << ptrShmem << endl;
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
    cout << "Lettore: disassocio memoria condivisa\n";
    if (shmdt(ptrShmem) == -1)
    {
        cerr << "Errore nel dissociare la memoria condivisa." << endl;
        perror("Details");
        return 1;
    }

    cout << "Lettore: finito!" << endl;

    return 0;
}