#include <iostream>
#include <fcntl.h>	 // per la open
#include <sys/shm.h> // server di memoria condivisa
#include <sys/mman.h>
#include <semaphore.h>
using namespace std;

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

	mcFd = shm_open(MEM_NAME, O_RDONLY, 0666);
	shmPtr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, mcFd, 0);

	/* Apertura del semaforo semFull */
	semFull = sem_open(SEM_FULL, O_EXCL);

	/* Apertura del semaforo semEmpty */
	semEmpty = sem_open(SEM_EMPTY, O_EXCL);

	for (int j = 0; j < 10; ++j)
	{
		shmCurPtr = shmPtr;

		cout << "WAIT Full (semFull)" << endl;

		/* Wait del semaforo semFull*/
		sem_wait(semFull);

		for (int i = 0; i < 200; ++i)
		{
			cout << *(shmCurPtr++);
		}

		cout << "POST Empty (semEmpty)" << endl;
		/* Post (signal) del semaforo semEmpty */
		sem_post(semEmpty);
	}

	/* Chiusura e rilascio dei semafori */
	sem_unlink(SEM_FULL);
	sem_unlink(SEM_EMPTY);

	/* Rilascio della memoria condivisa */
	shm_unlink(MEM_NAME);
	return 0;
}
