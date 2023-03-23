/**
 * Esempio di generazione di thread mediante libreria OpenMP
 * 
 * Per compilare correttamente il srgente va utilizzato il flag -fopenmp
 * e indicare la libreria per il link dinamico -lgomp.
 * Es. g++ -fopenmp -lgomp -o openmp_example openmp_example.cpp
 *
 * Riferimento alle slide
 * File: SODTR_05_Thread [I Thread]
 * Slide: OpenMP [#33]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    # pragma omp parallel
    {
        printf("Sono un mondo parallelo!. Ciao da Terra-%d!\n", gettid());
    }

    return 0;
}