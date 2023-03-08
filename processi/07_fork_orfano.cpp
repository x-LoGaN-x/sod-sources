/**
 * Generazione di un processo orfano.
 * In questo esempio il processo padre e il processo figlio condivideranno
 * lo stesso codice.
 * Il processo padre termina prima del figlio senza effettuare la chiamata wait.
 * In queste sitauzione il processo figlio diventerà orfano. In Linux il processo
 * orfano verrà "adottato" da un nuovo processo.
 *
 * Riferimento alle slide
 * File: SODTR_03_Processi [I Processi]
 * Slide: Processo orfano [#38]
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

   // Richiamo del comando di sistema ps
   system("ps -f");

   // Generazione di un nuovo processo figlio.
   // Il PID verrà assegnato alla variabile luke
   luke = fork();

   if (luke == 0)
   {
      // Processo figlio
      cout << "Io sono il figlio: pid " << getpid() << " parent pid " << getppid() << endl;
      sleep(5); // Attesa di 5 secondi
      cout << "Io sono il figlio: pid " << getpid() << " | Parent pid " << getppid() << endl;

      system("ps -f");
   }
   else
   {
      // Processo padre
      cout << "IO SONO TUO PADRE!!! Pid " << getpid() << " | Parent pid " << getppid() << " | Child pid " << luke << endl;
      sleep(2); // Attesa di 2 secondi

      // Richiesta di uscita da parte del padre
      exit(0);
   }

   return 0;
}