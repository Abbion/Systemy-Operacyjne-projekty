#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>

void zpais(int p_zapis, FILE* plik, int l_znakow)
{
    char c_zapis[1];
    for (int i = 0; i < l_znakow; i++)
    {
        c_zapis[0] = rand() % 93 + 33;

        if(write(p_zapis, c_zapis, 1)  < 0)
        {
            if(errno == EINTR)
                zpais(p_zapis, plik, l_znakow);
            
            else
            {
                perror("Blad podczas zapisu:\n");
                exit(EXIT_FAILURE);
            }
        }
        else
            fputc(c_zapis[0], plik);
    }
}

int main(int argc, char **argv)
{
    //Tworzenie pliku----------------------------
    //printf("Nowy producent: %d\n", getpid());
    int l_znakow = atoi(argv[1]);
    int p_zapis = atoi(argv[2]);
    srand(getpid());

    char filename[256] = "we_";
    char pid[16];
    sprintf(pid, "%d", getpid());
    strcat(filename, pid);
    strcat(filename, ".txt");

    FILE* plik = fopen(filename, "w");
    //-------------------------------------------

    //Zapis i generowanie znaków-----------------
    zpais(p_zapis, plik, l_znakow);
    //-------------------------------------------

    if(close(p_zapis) == -1)
    {
        printf("Blad[producent] podczas zamykwania potoku\n");
    }
    fclose(plik);

    return 0;
}