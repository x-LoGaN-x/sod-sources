/*
primo esempio di thread:
* thread creation
*/

#include <iostream>
#include <pthread.h>
using namespace std;

#define SPLIT(n, char) cout << string(n, char) << endl

/**
 * @brief Funzione per l'implementazione del thread.
 *
 * @return void*
 */
void *myThread(void *);

int main()
{
    int reply,
        scope;

    pthread_attr_t attr; // struttura dell'attributo

    pthread_attr_init(&attr); // attributi di default

    /**
     * Richiesta dell'ambito di contesa
     *
     * int pthread_attr_getscope(const pthread_attr_t *attr, int *scope);
     *
     * La funzione The pthread_attr_getscope() ritorna l'ambito della contesa configurata negli attributi
     * del thread e referenziata da attr all'interno della buffer puntato da scope.
     *
     * Maggiori info man pthread_attr_getscope
     */
    reply = pthread_attr_getscope(&attr, &scope);

    if (reply != 0)
    {
        cerr << "Errore nella lettura dell'ambito della contesa." << endl;
        perror("Details");
    }
    else
    {
        if (scope == PTHREAD_SCOPE_PROCESS)
        {
            cout << "L'ambito della contesa è impostata su PCS" << endl;
        }
        else if (scope == PTHREAD_SCOPE_SYSTEM)
        {
            cout << "L'ambito della contesa è impostata su SCS" << endl;
        }
        else
        {
            cerr << "Valore dell'ambito della contesa non ammesso" << endl;
            perror("Details");
        }
    }

    /**
     * Modifica dell'ambito della contesa
     *
     * int pthread_attr_setscope(pthread_attr_t *attr, int scope);
     *
     * La funzione pthread_attr_setscope() imposta l'attributo relativo all'ambito della contesa
     * dell'oggetto thread attributes a cui fa riferimento attr al valore specificato in scope.
     * L'attributo contention scope definisce l'insieme di thread con cui un thread compete per le
     * risorse, come la CPU.
     *
     * Maggiori info man pthread_attr_setscope
     */
    reply = pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
    if (reply != 0)
    {
        if (reply == ENOTSUP)
        {
            cerr << "La contesa PCS non è supportata in Linux" << endl;
        }
        else if (reply == EINVAL)
        {

            cerr << "Il valore specificato in scope non è valida" << endl;
        }
        else
        {
            cerr << "Errore non gestito" << endl;
        }
    }

    reply = pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    if (reply != 0)
    {
        if (reply == ENOTSUP)
        {
            cerr << "La contesa PCS non è supportata in Linux" << endl;
        }
        else if (reply == EINVAL)
        {

            cerr << "Il valore specificato in scope non è valida" << endl;
        }
        else
        {
            cerr << "Errore non gestito" << endl;
        }
    }

    pthread_t tid;

    pthread_create(&tid, &attr, myThread, NULL);

    pthread_join(tid, NULL);
}

void *myThread(void *)
{
    cout << "Hello world! I'm a simple thread!!! 😁" << endl;
    pthread_exit(NULL);
}