/**
 * Interazione con l'ambiente di programmazione in LINUX.
 * Prima di lanciare il main() LINUX chiama una startup che prende le
 * variabili d'ambiente, gli argomenti da riga di comando (ed altro ancora)
 * e le passa al main() che è stato generato in precedenza mediante le
 * chiamate fork/exec.
 * Al termine del processo LINUX esegue una end routine.
 *
 *
 * Slide: Creazione di un processo in UNIX
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <iostream>
#include <stdlib.h> // per getenv e setenv
#include <cerrno>
#include <cstring>
using namespace std;

#define SPLIT(n, char) cout << string(n, char) << endl

void fancyHeader(string title, int hLen = 50)
{
    int titleSpace, spaceBefore, spaceAfter;

    titleSpace = hLen - (title.length() + 2);
    spaceBefore = titleSpace / 2;
    spaceAfter = spaceBefore + titleSpace % 2;

    cout << string(hLen, '#') << endl;
    cout << "#" << string(hLen - 2, ' ') << "#" << endl;
    cout << "#" << string(spaceBefore, ' ') << title << string(spaceAfter, ' ') << '#' << endl;
    cout << "#" << string(hLen - 2, ' ') << "#" << endl;
    cout << string(hLen, '#') << endl;
}

/**
 * La variabile environ è un puntatore ad un array di puntatori a stringa
 * chiamato "environment". L'ultimo puntatore di questo array ha valore NULL.
 *
 * Si può utilizzare il comando 'man environ' per ottere maggiori dettagli
 * su questa variabile.
 */
extern char **environ;

/**
 * Il main ha 3 parametri. Il terzo parametro non fa parte dello standard
 * C, ma è ammesso da molti compilatori e svolge la stessa funzione di
 * environ.
 */
int main(int argc, char **argv, char *mainEnv[])
{
    int i = 0;

    // Stampa a video degli argomenti passati da riga di comando
    fancyHeader("Gestione argomenti");
    cout << "Numero di argomenti passati: " << argc << endl
         << endl;
    cout << "Il nome del file eseguibile è: " << argv[0] << endl
         << endl;

    for (i = 1; i < argc; i++)
    {
        printf("Argomento %d = %s\n", i, argv[i]);
    }
    cout << endl;

    // Stampa a video di tutte le variabili d'ambiente mediante la variabile
    // environ
    fancyHeader("Variabili d'ambiente");
    i = 0;
    while (environ[i] != NULL)
    {
        cout << environ[i++] << endl;
        SPLIT(50, '=');
    }
    cout << endl;

    // Stampa a video di tutte le variabili d'ambiente mediante la variabile
    // mainEnv
    fancyHeader("Contenuto mainEnv");
    i = 0;
    while (mainEnv[i] != NULL)
    { // fa la stessa cosa di environ
        cout << mainEnv[i++] << endl;
        SPLIT(50, '_');
    }
    cout << endl;

    fancyHeader("Lettura e scrittura variabili d'ambiente");
    /**
     * Lettura di una variabile d'ambiente mediante getenv(). La funzione
     * ritorna un puntatore alla stringa contenente il valore della variabile
     * passata come parametro alla funzione getenv.
     * Per info 'man getenv'
     */
    char *val = getenv("USER"); // Chiediamo il valore della variabile USER
    cout << "L'utente corrente è: " << val << endl;

    /**
     * Configurazione di una variabile d'ambiente mediante setenv(). La funzione
     * ritorna 0 se l'operazione è riuscita o -1 in caso di errore.
     * Per info 'man setenv'
     */
    if (setenv("USER", "vader", 1))
    {
        // Errore
        cerr << "Errore durante l'esecuzione di setenv():" << strerror(errno) << endl;
        return 1;
    }

    cout << "Valore della variabile USER aggiornato" << endl;
    val = getenv("USER");
    cout << "L'utente corrente è: " << val << endl;
    return 0;
}