#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../sem.h"

void filozof(int nr);
void handler(int sig);

int id_sem;

int main()
{
    signal(SIGINT, handler);

    srand(time(NULL));
    id_sem = semafor_init(5);
    semafor_ustaw(id_sem, 1, 5);    

    for (int i = 0; i < 5; i++)
    {
        switch (fork())
        {
            case -1:
                    printf("Blad podczas tworzenia procesu pisarza\n");
                    exit(EXIT_FAILURE);
                    break;
            case 0:
            {
                signal(SIGINT, NULL);
                filozof(i);
            }
            break;

            default:
            break;
        }
    }
    

    for (int i = 0; i < 5; i++)
    {
        int potomny, status;
        potomny = wait(&status);

        if(potomny < 0)
        {
            printf("Blad podczas oczekiwania na zakonczenie procesu\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

void filozof(int nr)
{
    while (1)
    {    
        int mysl_t = (rand() % 4) + 1;
        int jedz_t = (rand() % 2) + 1;

        printf("Filozof mysli \t %d\n", getpid());
        sleep(mysl_t);
        semafor_p_2(id_sem, nr, (nr + 1) % 5);

        printf("Filozof je \t %d\n", getpid());
        sleep(jedz_t);
        semafor_v_2(id_sem, nr, (nr + 1) % 5);

    }
}

void handler(int sig)
{
    usun_semafor(id_sem);
    exit(EXIT_SUCCESS);
}