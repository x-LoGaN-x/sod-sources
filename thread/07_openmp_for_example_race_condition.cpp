/**
 * Esempio di race condition nei thread generati mediante libreria OpenMP
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
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int i, sum = 0, N = 20;

    int a[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
        b[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
        c[N];

#pragma omp parallel for
    for (i = 0; i < N; i++)
    {
        printf("Sono Terra-%d! Sto gestendo i=%d.\n", gettid(), i);
        c[i] = a[i] + b[i];
    }

    cout << "{";
    for (i = 0; i < N - 1; i++)
    {
        cout << c[i] << ",";
    }
    cout << c[N - 1] << "}" << endl;

#pragma omp parallel for
    for (i = 0; i < N; i++)
    {
        sum += i;
    }

    printf("Il valore di sum è %d.\n", sum);

    return 0;
}