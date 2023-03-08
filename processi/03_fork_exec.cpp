/**
 * Sostituzione dello spazio di memoria del figlio mediante exec().
 * 
 * Il processo padre attenderà il termine dell'esecuzione del processo
 * figlio mediante chiamata wait().
 * 
 * Il figlio sostituirà il suo spazio di memoria mediante la chiamata
 * execl(). Per maggiori informazioni sulla famiglia di chiamate exec()
 * da cli 'man exec'
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

int main()
{
   pid_t luke;

   int reply;

   // Generazione di un nuovo processo figlio.
   // Il PID verrà assegnato alla variabile luke
   luke = fork();

   if (luke < 0)
   {
      // Si è verificato un errore durante la creazione del processo
      cerr << "IT'S A TRAP!!! Generazione del processo fallita" << endl;
      exit(-1);
   }
   else if (luke == 0)
   {
      // Processo figlio
      // Chiamata di sistema per l'esecuzione di un nuovo processo
      reply = execl("/bin/ls", "ls", NULL);
      if (reply < 0)
      {
         cerr << "IT'S A TRAP!!! Errore nella chiamata execl" << endl;
         exit(-1);
      }
   }
   else
   {
      // Processo padre
      wait(NULL); // Il processo padre attende il completamento del figlio
      cout << "Il processo figlio ha terminato la sua esecuzione." << endl;
   }

   return 0;
}