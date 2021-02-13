#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <sys/errno.h>

#include "../sem.h"
#include "../pam.h"

void argument_checker(int argc, char *argv[], int *l_p, int *l_c, int *l_m);
int str_to_ing(char *val);
void process_checker(int l_p, int l_c);
void handler(int sig);

int id_sem;

int main(int argc, char *argv[])
{
    signal(SIGINT, handler);

    srand(time(NULL));
    //Deklaracja i sprawdzenie zmiennych---------
    int l_p, l_c, l_m;
    char id_pam_str_lc[24], id_pam_str_lp[24], id_pam_str_lcc[24];
    argument_checker(argc, argv, &l_p, &l_c, &l_m);
    process_checker(l_p, l_c);
    //-------------------------------------------

    //Ustawienie semaforów oraz pamięci współdzielonej
    id_sem = semafor_init(5);
    semafor_ustaw(id_sem, 1, 5);

    int id_pam_A = pamiec_init('A');
    int* adres_A = pamiec_dolacz(id_pam_A);
    int lc = 0;
    adres_A = &lc;

    int id_pam_B = pamiec_init('B');
    int* adres_B = pamiec_dolacz(id_pam_B);
    int lp = 0;
    adres_B = &lp;

    int id_pam_C = pamiec_init('C');
    int* adres_C = pamiec_dolacz(id_pam_C);
    int lcc = 0;
    adres_C = &lcc;

    sprintf(id_pam_str_lc, "%d", id_pam_A);
    sprintf(id_pam_str_lp, "%d", id_pam_B);
    sprintf(id_pam_str_lcc, "%d", id_pam_C);
    //-------------------------------------------

    //Pętla dla pisarzy--------------------------
    for (int i = 0; i < l_p; i++)
    {
        char rnd_str[24];
        sprintf(rnd_str, "%d", (rand() % 3) + 1);

        switch (fork())
        {
            case -1:
                    printf("Blad podczas tworzenia procesu pisarza\n");
                    exit(EXIT_FAILURE);
                    break;
            case 0:
            {
                int fail = execl("./p", "p", id_pam_str_lp, rnd_str, NULL);
                if(fail < 0)
                {
                    perror("Exel error: ");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            default:
            break;
        }
    }
    //-------------------------------------------


     //Pętla dla czytelników----------------------
    for (int i = 0; i < l_c; i++)
    {
        char rnd_str[24];
        sprintf(rnd_str, "%d", (rand() % 3) + 1);

        switch (fork())
        {
            case -1:
                    printf("Blad podczas tworzenia procesu pisarza\n");
                    exit(EXIT_FAILURE);
                    break;
            case 0:
            {
                int fail = execl("./c", "c", id_pam_str_lc, rnd_str, id_pam_str_lcc, argv[3], NULL);
                if(fail < 0)
                {
                    perror("Exel error: ");
                    exit(EXIT_FAILURE);
                }
                else
                    printf("Elo\n");
            }
            break;

            default:
            break;
        }
    }
    //-------------------------------------------
    
    
    //Czekanie na zakończenie procesów-----------
    for (int i = 0; i < l_p + l_c; i++)
    {
        int potomny, status;
        potomny = wait(&status);

        if(potomny < 0)
        {
            printf("Blad podczas oczekiwania na zakonczenie procesu\n");
            exit(EXIT_FAILURE);
        }
    }
    //-------------------------------------------

    usun_semafor(id_sem);

    return 0;
}


//Funkcja sprawdzająca poprawność argymetnów-----
void argument_checker(int argc, char *argv[], int *l_p, int *l_c, int *l_m)
{
    if(argc != 4)
    {
        printf("Blad zla ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]); j++)
        {
            if(!isdigit(argv[i][j]))
            {
                printf("Blad argumentow! Wartosc nie jest liczba\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    *l_p = str_to_ing(argv[1]);
    *l_c = str_to_ing(argv[2]);
    *l_m = str_to_ing(argv[3]);
}
//-------------------------------------------


//-------------------------------------------
int str_to_ing(char *val)
{
    long temp = strtol(val, NULL, 10);
    if(temp < 0 || temp > INT_MAX)
    {
        if(errno == ERANGE)
        {
            perror("Wartosc poza zakresem: ");
            exit(EXIT_FAILURE);
        }
        printf("Blad argumentow\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}
//-------------------------------------------


//Funkcja sprawdzająca ilość wolnych procesow
void process_checker(int l_p, int l_c)
{
    int id = getuid();
    char id_str[16];
    sprintf(id_str, "%d", id);

    char cmd[256] = "ps ux | grep ^";
    strcat(cmd, id_str);
    strcat(cmd, " | wc -l");

    FILE* f_limit = popen(cmd, "r");
    char buf[256];
    fgets(buf, 256, f_limit);
    pclose(f_limit);
    int aktualnie = atoi(buf);

    f_limit = popen("ulimit -u", "r");
    fgets(buf, 256, f_limit);
    pclose(f_limit);
    int max = atoi(buf);

    if(l_c + l_p > max - aktualnie)
    {
        printf("Nie mozna utworzyc %d procesow\n", l_c + l_p);
        exit(EXIT_FAILURE);
    }
}
//-------------------------------------------


//Hander dla ctrl + c------------------------
void handler(int sig)
{
    usun_semafor(id_sem);
    exit(EXIT_SUCCESS);
}
//-------------------------------------------