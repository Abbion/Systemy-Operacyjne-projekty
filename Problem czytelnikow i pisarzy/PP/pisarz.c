#include <stdio.h>
#include <stdlib.h>
#include "../pam.h"
#include "../sem.h"

void handler(int sig);

int id_pam, rnd;
int* lp;

int main(int argc, char *argv[])
{
    signal(SIGINT, handler);

    //Deklaracja i konwersja zmiennych-----------
    long temp;
    temp = strtol(argv[1], NULL, 10);   id_pam = temp;
    temp = strtol(argv[2], NULL, 10);   rnd = temp;
    //-------------------------------------------

    //Przyłączenie semaforów i pamięci współdzielonej
    int id_sem = semafor_init(5);
    lp = pamiec_dolacz(id_pam);
    //-------------------------------------------

    //w1 - 0
    //sp - 1
    //sc - 2
    //w2 - 3
    //w3 - 4

    //-------------------------------------------
    while (1)
    {
        semafor_p(id_sem, 3);
        (*lp) += 1;
        if((*lp) == 1)
            semafor_p(id_sem, 2);
        semafor_v(id_sem, 3);
        semafor_p(id_sem, 1);

        printf("Pisanie pid %d\n", getpid());
        sleep(rnd);

        semafor_v(id_sem, 1);
        semafor_p(id_sem, 3);
        (*lp) -= 1;
        if((*lp) == 0)
            semafor_v(id_sem, 2);
        semafor_v(id_sem, 3);
    }
    //-------------------------------------------
    
    return 0;
}

void handler(int sig)
{
    pamiec_odlacz(lp, id_pam);
    exit(EXIT_SUCCESS);
}