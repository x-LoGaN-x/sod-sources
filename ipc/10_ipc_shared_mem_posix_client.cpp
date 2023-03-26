#include <iostream>
#include <unistd.h>
#include <sys/shm.h> // server di memoria condivisa
#include <sys/mman.h>
#include <sys/stat.h> // per costanti mode
#include <fcntl.h>    // per costanti O_*
using namespace std;
int main()
{
    int mcFd;
    char *ptrShmem;

    /**
     * Creazzione e apertura della memoria condivisa
     *
     * int shm_open(const char *name, int oflag, mode_t mode);
     *
     * shm_open() crea e apre un nuovo (o ne apre uno esistente) oggetto di memoria condivisa POSIX.
     * Questo oggetto altro non è che un handle utilizzabile da un processo terzo per mappare (mmap)
     * la stessa regione di memoria condivisa.
     *
     * Maggiori info man shm_open.
     */
    mcFd = shm_open("MyMemory", O_RDONLY, 0666);
    if (mcFd == -1)
    {
        cerr << "Errore nell'apertura memoria condivisa" << endl;
        perror("Details");
        exit(-1);
    }

    /**
     * Mapping della memoria
     *
     * void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
     *
     * mmap() crea un nuovo mapping nello spazio di indirizzi del processo chiamante. L'indirizzo di partenza
     * è specificato da addr. L'argomento lenght specifica la lunghezza del mapping (deve essere maggiore di 0)
     *
     * Maggiori info man 2 mmap
     */
    ptrShmem = (char *)mmap(0, 4096, PROT_READ, MAP_SHARED, mcFd, 0);
    if (ptrShmem == MAP_FAILED)
    {
        cout << "Errore durante la mappatura della memoria" << endl;
        perror("Details");
        return -1;
    }

    // Scrittura nella memoria condivisa
    cout << (char *)ptrShmem;

    /**
     * Chiusura della memoria condivisa
     * 
     * int shm_unlink(const char *name);
     * 
     * La funzione shm_unlink() effettua la funzione inversa di shm_open()
     * rimuovendo un oggetto precedentemente creato.
     */
    if (shm_unlink("MyMemory") == -1)
    { // chiude memoria condivisa
        cerr << "Errore nella rimozione della memoria condivisa" << endl;
        perror("Details");
        exit(-1);
    }
    return 0;
}
