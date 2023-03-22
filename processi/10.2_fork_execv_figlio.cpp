/**
 * Sostituzione dello spazio di memoria del figlio mediante exec().
 *
 * Il processo padre attenderà il termine dell'esecuzione del processo
 * figlio mediante chiamata wait().
 *
 * Il figlio sostituirà il suo spazio di memoria mediante la chiamata
 * execlp(). Per maggiori informazioni sulla famiglia di chiamate exec()
 * da cli 'man exec'
 *
 * Le funzioni possono essere raggruppate in base alle lettere che seguono
 * il prefisso exec:
 *
 * l - execl(), execlp(), execle()
 *     queste funzioni accettano una lista di argomenti, il primo argomento
 *     sarà il nome del programma che verrà eseguito, l'ultimo il puntatore NULL.
 *
 * v - execv(), execvp(), execvpe()
 *     queste funzioni accettano un vettore di argomenti, il primo elemento
 *     deve contenere il nome del programma da invocare, l'ultimo elemento deve
 *     essere un puntatore NULL.
 *
 * e - execle(), execvpe()
 *     L'environment della chiamata viene specificato mediante l'argomento envp.
 *     Quest'ultimo è un array di puntatori a stringhe e deve essere terminato da
 *     un puntatore NULL.
 *
 * p - execlp(), execvp(), execvpe()
 *     Queste funzioni accedono alla variabile d'ambiente PATH per la ricerca
 *     dell'eseguibile.
 *
 * Riferimento alle slide
 * File: SODTR_03_Processi [I Processi]
 * Slide: Sostituzione dello spazio di memoria in UNIX [#30]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <iostream>
#include <unistd.h>
#include <wait.h>
using namespace std;

int main(int argc, char *argv[])
{
   cout << "Esecuzione dal processo figlio" << endl;

   for (int i = 0; i < argc; i++)
   {
      cout << i + 1 << " = " << argv[i] << endl;
   }

   return 0;
}