/**
 * Esempio di assegnazione delle variabili all'interno della memoria.
 *
 * Riferimento alle slide
 * File: SODTR_03_Processi [I Processi]
 * Slide: Struttura in memoria di un programma C [#6]
 *
 * Sistemi Operativi Dedicati - 2023
 * Università Politecnica delle Marche
 */
#include <iostream>
using namespace std;

extern char _etext, _edata, _end;

#define ETEXT (unsigned long)(&_etext)
#define EDATA (unsigned long)(&_edata)
#define END (unsigned long)(&_end)

#define SPLIT cout << string(80, '=') << endl

void checkPosition(const char *varName, void *varPtr) //unsigned long
{
    unsigned long varAddr = (unsigned long)(varPtr);

    if (varAddr < ETEXT)
    {
        fprintf(stderr, "La variabile è contenuta nel campo TEXT (%14p)!\n", (void *)(ETEXT));
    }
    else if (ETEXT < varAddr && varAddr < EDATA)
    {
        printf("La variabile %s si trova nella sezione DATA (%14p - %14p).\n", varName, (void *)(ETEXT), (void *)(EDATA - 1));
    }
    else if (EDATA < varAddr && varAddr < END)
    {
        printf("La variabile %s si trova nella sezione BSS (%14p - %14p).\n", varName, (void *)(EDATA), (void *)(END - 1));
    }
    else
    {
        printf("La variabile %s si trova nell'HEAP o nello STACK ( >= %14p).\n", varName, (void *)(END));
    }
}

int a = 1; // in DATA
int b;     // in BSS

int main(int argc, char **argv)
{
    printf("La sezione TEXT termina a: %p.\n", (void *)ETEXT); // _etext
    printf("La sezione DATA termina a: %p.\n", (void *)EDATA); // _edata
    printf("La sezione BSS  termina a: %p.\n", (void *)END);   // _end

    static int c = 2;                                              // in DATA
    static int d;                                                  // in BSS
    int e;                                                         // in STACK
    int *f = new int;                                              // in HEAP

    cout << endl;
    cout << "Indirizzi di memoria:" << endl;
    printf("Variabile globale inizializzata a: %p.\n", &a);
    checkPosition("a", &a);
    SPLIT;

    printf("Variabile statica inizializzata c: %p.\n", &c);
    checkPosition("c", &c);
    SPLIT;

    printf("Variabile globale NON inizializzata b: %p.\n", &b);
    checkPosition("b", &b);
    SPLIT;

    printf("Variabile statica NON inizializzata d: %p.\n", &d);
    checkPosition("d", &d);
    SPLIT;

    printf("Variabile locale e: %p.\n", &e);
    checkPosition("e", &e);
    SPLIT;

    printf("Puntatore alla variabile dinamica f: %p.\n",  &f);
    checkPosition("f", &f);
    SPLIT;

    printf("Variabile dinamica *f: %p.\n", f);
    checkPosition("*f", f);
    SPLIT;

    printf("Primo argomento : %p.\n", argv);
    checkPosition("argv", argv);
    SPLIT;

    return 0;
}
