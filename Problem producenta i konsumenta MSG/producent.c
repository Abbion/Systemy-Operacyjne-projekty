#include "sem.h"
#include "pam.h"

#include <time.h>

int main()
{
    srand(time(NULL));
    int sl = rand() % 3;

    //Otwarcie pliku i zainicjalizowanie semaforów oraz pamięci
    FILE* plik = fopen("we", "r");

    if(plik == NULL)
        printf("Nie mozna otworzyc pliku");

    int sem_id;
    if(semafor_sprawdz() > -1) //Czy semafory zostały stworzone
    {  
        sem_id = semafor_init();    //Nowe semafory
        semafor_ustaw(sem_id);
        semafor_v(sem_id, 1);
        printf("Oczekiwanie na konsumenta...\n");
        semafor_p(sem_id, 0);
    }

    else
    {
        sem_id = semafor_init();
        semafor_p(sem_id, 0);
        printf("Producen przyłączony\n");
        semafor_v(sem_id, 1);
    }

    int pam_id = pamiec_init();
    //-------------------------------------------

    //Przdział pamięci i ustawienie semaforów
    char* adres = pamiec_dolacz(pam_id);
    //-------------------------------------------

    //Wczytywanie do pamięci z pliku
    char temp = 0;
    while (temp != EOF)
    {
        semafor_p(sem_id, 0);   //Oczekiwanie na wysłanie
        temp = fgetc(plik);
        *adres = temp;          //Wysyłka
        //printf("T: %c\n", temp);
        //printf("wyslane %c\n", *adres);
        //sleep(sl);
        semafor_v(sem_id, 1);   //Informacja o wysyłke
    }
    //-------------------------------------------

    semafor_p(sem_id, 0);

    fclose(plik);                   //Zamknięcie pliku
    pamiec_odlacz(adres, pam_id);   //Odłączenie pamięci
    usun_semafor(sem_id);
    
    return 0;
}   
