#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../pam.h"
#include "../sem.h"


int main(int argc, char *argv[])
{
    //Deklaracja i konwersja zmiennych-----------
    int rnd;
    long temp;
    temp = strtol(argv[1], NULL, 10);   
    rnd = temp;
    //-------------------------------------------
    
    //Przyłączenie semaforów---------------------
    int id_sem = semafor_init(2);
    //-------------------------------------------


    //-------------------------------------------
    while(1)
    {
        semafor_p(id_sem, 1);
        printf("Pisanie pid %d\n", getpid());
        sleep(rnd);
        semafor_v(id_sem, 1);
    }
    //-------------------------------------------
    
    
    return 0;
}