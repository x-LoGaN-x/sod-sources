/*
 * pthread_attr_setschedpolicy
 */

#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define SPLIT(n, char) cout << string(n, char) << endl

void *myThread(void *name);

int main(int argc, char *argv[])
{
    int reply,
        myPriority;

    if (argc == 2)
    {
        myPriority = atoi(argv[1]);
        if (myPriority < 1 || myPriority > 99)
        {
            SPLIT(100, '-');

            cout << "La priorità richiesta è fuori dai limiti consentiti (1-99)." << endl
                 << "La priortià verrà impostata a 22." << endl;

            SPLIT(100, '-');

            myPriority = 22;
        }
    }
    else
    {
        myPriority = 22;
    }

    /**
     * La struttura timespec ha la forma seguente:
     *
     *      struct timespec
     *      {
     *          time_t tv_sec;
     *          long tv_nsec;
     *      };
     */
    struct timespec quantum;

    /**
     * Richiesta del valore del quanto di tempo
     *
     * int sched_rr_get_interval(pid_t pid, struct timespec *tp);
     *
     * sched_rr_get_interval() scrive nella struttura timespec puntata da tp il quanto
     * di tempo round-robin per il processo identificato da pid. Il processo specificato
     * deve essere in esecuzione secondo la politica di schedulazione SCHED_RR.
     *
     * Se pid è zero, il quanto di tempo del processo chiamante viene scritto in *tp.
     */
    sched_rr_get_interval(0, &quantum);

    cout << "Il padre ha un quanto di tempo di " << quantum.tv_sec << " secondi e "
         << quantum.tv_nsec / 1e6 << " millisecondi" << endl;

    pthread_attr_t attr;

    pthread_t tid;

    pthread_attr_init(&attr);

    /**
     * Configurazione dell'attributo detatch
     *
     * int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
     *
     * La funzione pthread_attr_setdetachstate() imposta l'attributo detach state dell'oggetto
     * thread attributes a cui fa riferimento attr sul valore specificato in detachstate. L'attributo
     * detachstate definisce se un thread creato utilizzando l'oggetto thread attributes attr sarà
     * creato in uno stato joinable o detached.
     *
     * I seguenti valori possono essere specificati in detachstate:
     * - PTHREAD_CREATE_DETACHED: i thread creati utilizzando attr saranno creati in uno stato distaccato.
     * - PTHREAD_CREATE_JOINABLE: i thread creati con attr saranno creati in uno stato joinable.
     *
     * L'impostazione predefinita dell'attributo detach state in un oggetto thread attributes appena
     * inizializzato è PTHREAD_CREATE_JOINABLE.
     *
     * Maggiori info man pthread_attr_setdetachstate
     */
    reply = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    if (reply != 0)
    {
        cerr << "Detach state: " << reply << endl;
    }

    /**
     * Configurazione dell'attributo inherit-scheduler
     *
     * int pthread_attr_setinheritsched(pthread_attr_t *attr, int inheritsched);
     *
     * La funzione pthread_attr_setinheritsched() imposta l'attributo inherit-scheduler dell'oggetto
     * thread attributes a cui fa riferimento attr al valore specificato in inheritsched. L'attributo
     * inherit-scheduler determina se un thread creato utilizzando l'oggetto thread attributes attr
     * erediterà i suoi attributi di pianificazione dal thread chiamante o se li prenderà da attr.
     *
     * L'attributo inherit-scheduler influisce sui seguenti attributi di scheduling:
     * - politica di scheduling (pthread_attr_setschedpolicy(3))
     * - priorità di scheduling (pthread_attr_setschedparam(3))
     * - ambito di contesa (pthread_attr_setschedparam(3)).
     *
     * I seguenti valori possono essere specificati in inheritsched:
     * - PTHREAD_INHERIT_SCHED: i thread creati con attr ereditano gli attributi di pianificazione
     *   dal thread creatore; gli attributi di pianificazione in attr vengono ignorati.
     * - PTHREAD_EXPLICIT_SCHED: i thread creati con attr prendono i loro attributi di pianificazione
     *   dai valori specificati dall'oggetto attributes.
     *
     * L'impostazione predefinita dell'attributo inherit-scheduler in un oggetto thread attributes
     * appena inizializzato è PTHREAD_INHERIT_SCHED.
     *
     * Maggiori info man pthread_attr_setinheritsched
     */
    reply = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    if (reply)
    {
        cerr << "Errore nella configurazione dell'ereditazione dello scheduler: " << reply << endl;
    }

    /**
     * Configurazione della politiva di scheduling
     *
     * int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy)
     *
     * La funzione pthread_attr_setschedpolicy() imposta l'attributo scheduling policy dell'oggetto thread
     * attributes a cui fa riferimento attr al valore specificato in policy. Questo attributo determina la
     * politica di pianificazione di un thread creato utilizzando l'oggetto thread attributes attr.
     *
     * I valori supportati per la politica sono SCHED_FIFO, SCHED_RR e SCHED_OTHER, con la semantica
     * descritta in sched(7).
     *
     * Affinché l'impostazione della politica fatta da pthread_attr_setschedpolicy() abbia effetto
     * quando si chiama pthread_create(3), il chiamante deve usare pthread_attr_setinheritsched(3) per
     * impostare l'attributo inherit-scheduler dell'oggetto attributi attr a PTHREAD_EXPLICIT_SCHED.
     *
     * Maggiori info man pthread_attr_setschedpolicy
     */
    reply = pthread_attr_setschedpolicy(&attr, SCHED_RR);
    if (reply)
    {
        cerr << "Detach policy: " << reply << endl;
    }

    /**
     * Struttura perla configurazione dei parametri di scheduling
     *
     * I parametri di pianificazione sono mantenuti nella seguente struttura:
     *
     *      struct sched_param
     *      {
     *           int sched_priority;
     *      };
     *
     * Come si può notare, è supportato un solo parametro di schedulazione.
     * Per i dettagli sugli intervalli consentiti per le priorità di scheduling in ogni
     * politica di scheduling, vedere sched(7).
     */
    struct sched_param mySched;

    mySched.sched_priority = myPriority;

    /**
     *
     *
     * int pthread_attr_setschedparam(pthread_attr_t *attr, const struct sched_param *param)
     *
     * La funzione pthread_attr_setschedparam() imposta gli attributi dei parametri di pianificazione
     * dell'oggetto thread attributes a cui fa riferimento attr ai valori specificati nel buffer a cui
     * punta param. Questi attributi determinano i parametri di pianificazione di un thread creato
     * utilizzando l'oggetto thread attributes attr.
     *
     * Affinché l'impostazione del parametro fatta da pthread_attr_setschedparam() abbia effetto
     * quando si chiama pthread_create(3), il chiamante deve usare pthread_attr_setinheritsched(3) per
     * impostare l'attributo inherit-scheduler dell'oggetto attributi attr a PTHREAD_EXPLICIT_SCHED.
     *
     * Maggiori info man pthread_attr_setschedparam
     */
    pthread_attr_setschedparam(&attr, &mySched);

    char name[] = "Bond, James Bond";

    reply = pthread_create(&tid, &attr, myThread, (void *)&name);
    if (reply != 0)
    {
        cout << "Creazione del thread error: " << reply << endl;
        perror("Details");
    }

    pthread_join(tid, NULL);
    pthread_attr_destroy(&attr);

    SPLIT(100, '-');

    cout << "Io sono tuo padre!" << endl;

    SPLIT(100, '-');

    pthread_exit(NULL);
}

void *myThread(void *name)
{
    pthread_t tid = pthread_self();

    pthread_attr_t selfAttr;

    struct sched_param selfSched;

    pthread_getattr_np(tid, &selfAttr);

    pthread_attr_getschedparam(&selfAttr, &selfSched);

    struct timespec selfQtm;

    sched_rr_get_interval(0, &selfQtm);

    SPLIT(100, '=');

    cout << "Hello world! Il mio nome è " << (char *)name << "!" << endl;
    cout << "Il mio ID è " << tid << ", e sono schedulato RR con priorità " << selfSched.sched_priority << endl;
    cout << "Il mio quanto di tempo è di " << selfQtm.tv_sec << " secondi e "
         << selfQtm.tv_nsec / 1e6 << " millisecondi" << endl;

    SPLIT(100, '=');

    sleep(10);

    pthread_exit(NULL);
}
