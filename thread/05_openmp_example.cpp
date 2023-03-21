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