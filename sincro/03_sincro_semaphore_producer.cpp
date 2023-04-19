#include <fcntl.h>	 // per la open
#include <unistd.h>	 // per ftruncate
#include <sys/shm.h> // server di memoria condivisa
#include <sys/mman.h>
#include <semaphore.h>
#include <iostream>

using namespace std;

#define ELAPSED(end, start) (double)((end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000)) / 1000

#define NUM_THREADS 5

#ifndef LOCAL_MUTEX
#define USE_MUTEX true
#endif

#define MEM_NAME "/shmSemExample"
#define SEM_FULL "/semFull"
#define SEM_EMPTY "/semEmpty"
#define SIZE 4096

int main()
{
	int mcFd;

	char *shmPtr,
		*shmCurPtr;

	sem_t *semFull,
		*semEmpty;

	mcFd = shm_open(MEM_NAME, O_CREAT | O_RDWR, 0666);
	ftruncate(mcFd, SIZE); // dimensiona il segmento di memoria

	shmPtr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mcFd, 0);

	// Crea il semaforo con nome semFull e lo inizializza a "ROSSO"
	semFull = sem_open(SEM_FULL, O_CREAT, S_IRUSR | S_IWUSR, 0);

	// Crea il semaforo con nome semEmpty e lo inizializza a "VERDE"
	semEmpty = sem_open(SEM_EMPTY, O_CREAT, S_IRUSR | S_IWUSR, 1);

	for (int j = 0; j < 10; ++j)
	{
		shmCurPtr = shmPtr;

		cout << "WAIT Empty (semEmpty)" << endl;
		/* Wait del semaforo semEmpty*/
		sem_wait(semEmpty);
		cout << "Prova" << endl;

		for (int i = 0; i < 200; ++i)
		{
			*(shmCurPtr++) = (j + 48);
		}

		cout << "POST Full (semFull)" << endl;
		/* Post (signal) del semaforo semFull */
		sem_post(semFull);
	}

	cout << "STOP" << endl;

	return 0;
}
