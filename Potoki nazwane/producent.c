#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/resource.h>
#include <time.h>
#include <ctype.h>

#define NAZWA_FIFO "./k_fifo"

//Funckje pomocnicze------------
void generate(int l_z, int potok, FILE* plik);
FILE* generateFile();
void argument_checker(int argc, char *argv[], int* l_p, int* l_z);
void process_checker(int l_p);
//------------------------------

int main(int argc, char *argv[])
{
    //Sprawdzenie argumetnow----
    int l_p, l_z;
    argument_checker(argc, argv, &l_p, &l_z);
    //printf("l_p: %d, l_z: %d\n", l_p, l_z);
    process_checker(l_p);
    //--------------------------

    srand(time(NULL));

    //Tworzenie potoku fifo-----
    if(access(NAZWA_FIFO, F_OK) == -1)
    {
        int res = mkfifo(NAZWA_FIFO, 0600);
        if(res != 0)
        {
            perror("Blad podczas tworzenia kolejki fifio: ");
            exit(EXIT_FAILURE);
        }
    }
    //--------------------------

    //Otwarcie potoku-----------
    printf("Program czeka na podpiecie klientow...\n");
    int potok=open(NAZWA_FIFO, O_WRONLY);
    if(potok < 0)
    {
        perror("Nie mozna otworzyc kolejki fifo do zapisu");
        exit(EXIT_FAILURE);
    }
    printf("Wykryto klientow\n");
    //--------------------------

    //Pętla tworząca producentow
    for (int i = 0; i < l_p; i++)
    {
        switch (fork())
        {
            case -1:
                    printf("Blad podczas tworzenia watku producenta\n");
                    exit(EXIT_FAILURE);
                    break;
            case 0:
            {
                FILE* plik = generateFile();
                generate(l_z, potok, plik);
            }
            break;

            default:
            break;
        }
    }
    //--------------------------
    
    //Czekanie na zakończenie procesów
    for (int i = 0; i < l_p; i++)
    {
        int potomny, status;
        potomny = wait(&status);
        if(potomny < 0)
        {
            perror("Bload podczas czekania na zakonczenie potomka");
            exit(EXIT_FAILURE);
        }
    }
    //--------------------------

    close(potok);

    return 0;
}


//Funkcja generująca i zapisująca znaku
void generate(int l_z, int potok, FILE* plik)
{
    char c_zapis[1];
    for (int i = 0; i < l_z; i++)
    {
        c_zapis[0] = rand() % 93 + 33;
        //printf("Wygenerowano: %s\n", c_zapis);
        if(write(potok, c_zapis, 1)  < 0)
        {
            if(errno == EINTR)
                generate(l_z, potok, plik);
            
            else
            {
                perror("Blad podczas zapisu:\n");
                exit(EXIT_FAILURE);
            }
        }
        else
            fputc(c_zapis[0], plik);
    }
    
    close(potok);
    fclose(plik);
    exit(EXIT_SUCCESS);
}
//-----------------------------


//Funkcja generująca plik do zapisu dla danego procesu
FILE* generateFile()
{
    //Tworzenie pliku-----------
    srand(getpid());

    char filename[256] = "we_";
    char pid[16];
    sprintf(pid, "%d", getpid());
    strcat(filename, pid);
    strcat(filename, ".txt");

    FILE* plik = fopen(filename, "w");
    //--------------------------
    return plik;
}
//-----------------------------


//Funkcja sprawdzająca poprawność argymetnów
void argument_checker(int argc, char *argv[], int* l_p, int* l_z)
{
    if(argc != 3)
    {
        printf("Blad zla ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Blad argumentow! Wartosc nie jest liczba\n");
            exit(EXIT_FAILURE);
        }
    }
    
    for (int i = 0; i < strlen(argv[2]); i++)
    {
        if(!isdigit(argv[2][i]))
        {
            printf("Blad argumentow! Wartosc nie jest liczba\n");
            exit(EXIT_FAILURE);
        }
    }

    long temp_p = strtol(argv[1], NULL, 10);
    long temp_z = strtol(argv[2], NULL, 10);
    if(temp_p < 0 || temp_p > INT_MAX || temp_z < 0 || temp_z > INT_MAX)
    {
        //if(errno == ERANGE)
        printf("Blad argumentow\n");
        exit(EXIT_FAILURE);
    }

    *l_p = temp_p;
    *l_z = temp_z;
}
//-----------------------------


//Funkcja sprawdzająca ilość wolnych procesow
void process_checker(int l_p)
{
    /*
    int id = getgid();
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

    if(l_p > max - aktualnie)
    {
        printf("Nie mozna utworzyc %d procesow\n", l_p);
        exit(EXIT_FAILURE);
    }

    FILE* ps_pl = fopen("ps", "w");
    fprintf(ps_pl, "%d", l_p);
    fclose(ps_pl);
    */
}
//-----------------------------