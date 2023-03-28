#include <iostream>
#include <unistd.h>  // per ftruncate()
#include <sys/shm.h> // server di memoria condivisa
#include <sys/mman.h>
#include <sys/stat.h> // per costanti mode
#include <fcntl.h>    // per costanti O_*
#include <cstring>
using namespace std;
int main()
{
    const char *msg[] = {"Sono ",
                         "scritto ",
                         "nella ",
                         "memoria ",
                         "condivisa\n"};
    int mcFd;
    char *ptrShmem;

    /**
     * Creazione e apertura della memoria condivisa
     *
     * int shm_open(const char *name, int oflag, mode_t mode);
     *
     * shm_open() crea e apre un nuovo (o ne apre uno esistente) oggetto di memoria condivisa POSIX.
     * Questo oggetto altro non è che un handle utilizzabile da un processo terzo per mappare (mmap)
     * la stessa regione di memoria condivisa.
     *
     * Maggiori info man shm_open.
     */
    mcFd = shm_open("MyMemory", O_CREAT | O_RDWR, 0666);
    if (mcFd == -1)
    {
        cerr << "Errore nell'apertura memoria condivisa" << endl;
        perror("Details");
        exit(-1);
    }

    // Dimensionamento della memoria
    ftruncate(mcFd, sizeof(msg));

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
    ptrShmem = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, mcFd, 0);
    if (ptrShmem == MAP_FAILED)
    {
        cout << "Errore durante la mappatura della memoria" << endl;
        perror("Details");
        return -1;
    }

    // Scrittura nel segmento di memoria condivisa
    for (int i = 0; i < strlen(*msg); ++i)
    {
        sprintf(ptrShmem, "%s", msg[i]);
        ptrShmem += strlen(msg[i]);
    }

    /**
     * Deallocazione della memoria condivisa
     *
     * int munmap(void *addr, size_t length);
     *
     * La chiamata di sistema munmap() rimuove il mapping specificando il range di indirizzi.
     * Il mappin alla regione è comunque rimosso automaticamente al termine del processo.
     * Chiudere il descrittore del file, invece, non rimuoverà il mapping della memoria.
     *
     * Maggiori info man 2 munmap
     */
    munmap(ptrShmem, 4096); // dealloca memoria condivisa
    return 0;
}
