/**
 * Passaggio del processo figlio nello stato zombie.
 * In questo esempio il processo padre e il processo figlio condivideranno
 * lo stesso codice.
 * Dopo la terminazione del processo figlio, questo entra nello stato zombie,
 * fintanto che il processo padre non invoca la wait().
 *
 * Riferimento alle slide
 * File: SODTR_03_Processi [I Processi]
 * Slide: Processo zombie [#35]
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

   // Generazione di un nuovo processo figlio.
   // Il PID verrà assegnato alla variabile luke
   luke = fork();

   if (luke == 0)
   {
      // Processo figlio

      // Richiamo del comando di sistema ps
      cout << "Io sono il figlio: pid " << getpid() << " parent pid " << getppid() << endl;
      system("ps -f");
      exit(0);
   }
   else
   {
      // Processo padre
      sleep(5); // Attesa di 5 secondi
      cout << "IO SONO TUO PADRE!!! Pid " << getpid() << " | Parent pid " << getppid() << " | Child pid " << luke << endl;
      system("ps -aux | grep Z");
      wait(NULL);
      system("ps -aux | grep Z");
   }

   return 0;
}