#include "sem.h"

int main()
{
    FILE *plik = fopen("wynik.txt", "a");
    int sm = semafor_init();
    //status(sm);

    printf("Sekcja t21 procesu o PID: %d\n", getpid());
    fprintf(plik, "Sekcja t21 procesu o PID: %d\n", getpid());
    fflush(plik);
    sleep(1);
    semafor_v(sm, 2);
    semafor_p(sm, 1);

    printf("Sekcja t22 procesu o PID: %d\n", getpid());
    fprintf(plik, "Sekcja t22 procesu o PID: %d\n", getpid());
    fflush(plik);
    sleep(1);
    semafor_v(sm, 0);
    semafor_p(sm, 1);

    printf("Sekcja t23 procesu o PID: %d\n", getpid());
    fprintf(plik, "Sekcja t23 procesu o PID: %d\n", getpid());
    fflush(plik);
    sleep(1);
    semafor_v(sm, 2);

    fclose(plik);
    return 0;
}