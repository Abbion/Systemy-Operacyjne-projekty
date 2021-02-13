#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/errno.h>

int main(int argc, char **argv)
{
    //Argumenty----------------------------------
    if(argc != 4)   //Pierwszy argument to nazwa programu
    {
        printf("Blad: zla ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    int l_konsument = atoi(argv[1]);
    int l_producent = atoi(argv[2]);

    long test_znakow = strtol(argv[3], NULL, 10);
    if(test_znakow == 0)
    {
        if(errno == EINVAL)
        {
            perror("Bledna ilosc znakow: ");
            exit(EXIT_FAILURE);
        }
    }


    if(l_konsument < 1 || l_producent < 1 || test_znakow < 1 || test_znakow > 2147483647)
    {
        printf("Blad: bledne wartosci argumentow\n");
        exit(EXIT_FAILURE);
    }

    int l_znakow = test_znakow;
    //-------------------------------------------
    
    int potok[2];
    if(pipe(potok) < 0)
    {
        perror("Blad podczas tworzenia potku: ");
        exit(EXIT_FAILURE);
    }
    char c_potok_0[16];
    sprintf(c_potok_0, "%d", potok[0]);
    char c_potok_1[16];
    sprintf(c_potok_1, "%d", potok[1]);
    printf("deskyptory: %d, %d\n", potok[0], potok[1]);
    printf("l_k: %d, l_p: %d, l_z %d, pid: %d\n", l_konsument, l_producent, l_znakow, getpid());
    for (int i = 0; i < l_producent; i++)
    {
        switch(fork())
        {
            case -1:
                printf("Blad podczas tworzenia watku producenta\n");
                exit(EXIT_FAILURE);
                break;
            case 0:
                close(potok[2]);
                execl("./p", "p", argv[3], c_potok_1, NULL);
            break;
            default:
            break;
        }
    }
    for (int i = 0; i < l_konsument; i++)
    {
         switch(fork())
        {
            case -1:
                printf("Blad podczas tworzenia watku konsumenta\n");
                exit(EXIT_FAILURE);
                break;
            case 0:
                close(potok[1]);
                execl("./k", "k", c_potok_0, NULL);
            break;
            default:
            break;
        }
    }
    
    close(potok[1]);
    //sleep(1);
    for (int i = 0; i < l_producent + l_konsument; i++)
    {
        int potomny, status;
        potomny = wait(&status);
    }

    return 0;
}