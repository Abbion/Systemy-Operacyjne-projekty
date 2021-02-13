#include "sem.h"

int main()
{
    FILE *plik = fopen("wynik.txt", "a");
    int sm = semafor_init();

    semafor_p(sm, 0);
    printf("Sekcja t11 procesu o PID: %d\n", getpid());
    fprintf(plik, "Sekcja t11 procesu o PID: %d\n", getpid());
    sleep(1);

    printf("Sekcja t12 procesu o PID: %d\n", getpid());
    fprintf(plik, "Sekcja t12 procesu o PID: %d\n", getpid());
    fflush(plik);
    sleep(1);
    semafor_v(sm, 1);

    fclose(plik);
    return 0;
}