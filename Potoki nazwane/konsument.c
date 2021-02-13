#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/resource.h>

#define NAZWA_FIFO "./k_fifo"

//Funckje pomocnicze------------
void readFifo(int potok, FILE* plik);
FILE* generateFile();
void argument_checker(int argc, char *argv[], int* l_k);
void process_checker(int l_k);
//------------------------------

int main(int argc, char *argv[])
{
    //Sprawdzenie argumetnow----
    int l_k;
    argument_checker(argc, argv, &l_k);
    //printf("l_k: %d\n", l_k);
    process_checker(l_k);
    //Sprawdzenie argumetnow----

    //Otwarcie potoku-----------
    printf("Program czeka na podpięcie konsumentow...");
    int potok = open(NAZWA_FIFO, O_RDONLY);
    printf("Wykryto konsumentow\n");
    //--------------------------


    //Pętla tworząca konsumentow
    for (int i = 0; i < l_k; i++)
    {
        switch (fork())
        {
            case -1:
                    printf("Blad podczas tworzenia procesu producenta\n");
                    exit(EXIT_FAILURE);
                    break;
            case 0:
                {
                FILE* plik = generateFile();
                readFifo(potok, plik);
                }
            break;

            default:
            break;
        }
    }
    //--------------------------

    //Czekanie na zakończenie procesów
    for (int i = 0; i < l_k; i++)
    {
        int potomny, status;
        potomny = wait(&status);
    }
    //--------------------------

    close(potok);
    unlink(NAZWA_FIFO);

    return 0;
}


//Funkcja generująca i zapisująca znaku
void readFifo(int potok, FILE* plik)
{
    char buffor[1];

    while (1)
    {
        int stan = read(potok,buffor,1);
        
        if(stan < 0)
        {
            perror("Blad podczas zapisu\n");
            exit(EXIT_FAILURE);
        }

        else if(stan == 0)
        {
            close(potok);
            break;
        }
        
        else
            fputc(buffor[0], plik);
    }
    
    close(potok);
    exit(EXIT_SUCCESS);
}
//-----------------------------


//Funkcja generująca plik do zapisu dla danego procesu
FILE* generateFile()
{
    //Tworzenie pliku-----------
    srand(getpid());

    char filename[256] = "wy_";
    char pid[16];
    sprintf(pid, "%d", getpid());
    strcat(filename, pid);
    strcat(filename, ".txt");

    FILE* plik = fopen(filename, "w");
    //--------------------------
    return plik;
}
//------------------------------


//Funkcja sprawdzająca poprawność argymetnów
void argument_checker(int argc, char *argv[], int* l_k)
{
    if(argc != 2)
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

    long temp_k = strtol(argv[1], NULL, 10);
    if(temp_k < 0 || temp_k > INT_MAX)
    {
        //if(errno == ERANGE)
        printf("Blad argumentow\n");
        exit(EXIT_FAILURE);
    }

    *l_k = temp_k;
}
//------------------------------


//Funkcja sprawdzająca ilość wolnych procesow
void process_checker(int l_k)
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


    FILE* ps_pl = fopen("ps", "r");
    if(ps_pl == NULL)
    {
        printf("Nie mozna sprawdzic ilosci procesow producenta\n");
        exit(EXIT_FAILURE);
    }
    fseek(ps_pl, 0, SEEK_END);
    if(ftell(ps_pl) == 0)
    {
        printf("Nie wykryto producenta\n");
        exit(EXIT_FAILURE);
    }
    int l_p;
    fscanf(ps_pl, "%d", &l_p);
    fclose(ps_pl);

    ps_pl = fopen("ps", "w");
    fclose(ps_pl);

    if(l_k + l_p > max - aktualnie)
    {
        printf("Nie mozna utworzyc %d procesow\n", l_k);
        exit(EXIT_FAILURE);
    }
    */
}
//-----------------------------