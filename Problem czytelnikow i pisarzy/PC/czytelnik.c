#include <stdio.h>
#include <stdlib.h>
#include "../pam.h"
#include "../sem.h"

int id_pam, rnd, id_pam_lcc, lm;
int* lc;
int* lcc;
void handler(int sig);

int main(int argc, char *argv[])
{
    signal(SIGINT, handler);

    //Deklaracja i konwersja zmiennych-----------
    long temp;
    temp = strtol(argv[1], NULL, 10);   id_pam = temp;
    temp = strtol(argv[2], NULL, 10);   rnd = temp;
    temp = strtol(argv[3], NULL, 10);   id_pam_lcc = temp;
    temp = strtol(argv[4], NULL, 10);   lm = temp;
    //-------------------------------------------
    
    //Przyłączenie semaforów i pamięci współdzielonej
    int id_sem = semafor_init(2);
    lc = pamiec_dolacz(id_pam);
    lcc = pamiec_dolacz(id_pam_lcc);
    //-------------------------------------------


    //-------------------------------------------
    while(1)
    {
        while((*lcc) >= lm);

        semafor_p(id_sem, 0);
        (*lcc) += 1;
        (*lc) += 1;
        if(*lc == 1)
            semafor_p(id_sem, 1);

        semafor_v(id_sem, 0);
        printf("Czytanie pid %d\n", getpid());
        sleep(rnd);
        semafor_p(id_sem, 0);
        
        (*lc) -= 1;
        if((*lc) == 0)
            semafor_v(id_sem, 1);
        semafor_v(id_sem, 0);

        (*lcc) -= 1;
    }
    //-------------------------------------------
    

    return 0;
}

void handler(int sig)
{
    pamiec_odlacz(lc, id_pam);
    pamiec_odlacz(lcc, id_pam_lcc);
    exit(EXIT_SUCCESS);
}