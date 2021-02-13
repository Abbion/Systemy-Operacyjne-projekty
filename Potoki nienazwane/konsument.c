#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>

void odczyt(int p_odczyt, FILE* plik)
{
    char c_odczyt[1];
    while (1)
    {
        int stan = read(p_odczyt,c_odczyt,1);
        
        if(stan < 0)
        {
            if(errno == EINTR)
            {
                odczyt(p_odczyt, plik);
            }
            else
            {
                perror("Blad podczas zapisu\n");
                exit(EXIT_FAILURE);
            }
        }

        else if(stan == 0)
            break;

        else
            fputc(c_odczyt[0], plik);
    }
}

int main(int argc, char **argv)
{
    //Tworzenie pliku----------------------------
    int p_odczyt = atoi(argv[1]);
    //printf("Nowy konsument %d\n", getpid());

    char filename[256] = "wy_";
    char pid[16];
    sprintf(pid, "%d", getpid());
    strcat(filename, pid);
    strcat(filename, ".txt");

    FILE* plik = fopen(filename, "w");
    //-------------------------------------------

    //Zapisanie danych ze strumienia do pliku----
    odczyt(p_odczyt, plik);
    //-------------------------------------------

    fclose(plik);

    return 0;
}