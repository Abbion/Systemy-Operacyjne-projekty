#include "sem.h"
#include "pam.h"

#include <time.h>

int main()
{
    srand(time(NULL));
    int sl = rand() % 3;

    //Otwarcie pliku i zainicjalizowanie semaforów oraz pamięci
    key_t klucz = ftok(".", 'A');
    FILE* plik = fopen("wy", "w");
    if(plik == NULL)
        printf("Nie mozna otworzyc pliku");

    
    int sem_id;
    if(semafor_sprawdz() > -1) //Czy semafory zostały stworzone
    {  
        sem_id = semafor_init();    //Nowe semafory
        semafor_ustaw(sem_id);
        semafor_v(sem_id, 0);
        printf("Oczekiwanie na producenta...\n");
        semafor_p(sem_id, 1);
    }

    else
    {
        sem_id = semafor_init();
        semafor_p(sem_id, 1);
        printf("Konsument przyłączony\n");
        semafor_v(sem_id, 0);
    }

    int pam_id = pamiec_init();
    //-------------------------------------------
    
    //Przdział pamięci
    char* adres = pamiec_dolacz(pam_id);
    //-------------------------------------------

    //Gotowość do przyjmowania informacji
    semafor_v(sem_id, 0);
    //-------------------------------------------

    //Wczytywanie wartości z adresu
    while (1)
    {
        semafor_p(sem_id, 1);   //Oczekiwanie na nadejście
        if(*adres == EOF)       //Sprawdzenie czy to nie jest koniec pliku
        {
            semafor_v(sem_id, 0);   //Informacja o zakończeniu wczytywania
            break;
        }

        fprintf(plik, "%c", *adres);    //Zapisanie informacji do pliku
        semafor_v(sem_id, 0);           //Informacja otrzymaniu informacji
    }
    //-------------------------------------------
    
    fclose(plik);                   //Zamknięcie pliku
    pamiec_odlacz(adres, pam_id);   //Odłączenie pamięci

    return 0;
}   