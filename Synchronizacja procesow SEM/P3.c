#include "sem.h"

int main()
{
    FILE *plik = fopen("wynik.txt", "a");
    int sm = semafor_init();

    semafor_p(sm, 2);
    printf("Sekcja t31 procesu o PID: %d\n", getpid());
    fprintf(plik, "Sekcja t31 procesu o PID: %d\n", getpid());
    sleep(1);

    printf("Sekcja t32 procesu o PID: %d\n", getpid());
    fprintf(plik, "Sekcja t32 procesu o PID: %d\n", getpid());
    fflush(plik);
    sleep(1);
    semafor_v(sm, 1);
    semafor_p(sm, 2);

    printf("Sekcja t33 procesu o PID: %d\n", getpid());
    fprintf(plik, "Sekcja t33 procesu o PID: %d\n", getpid());
    fflush(plik);
    sleep(1);

    fclose(plik);
    return 0;
}