#include "sem.h"

#define ILE_SEM 3

int main()
{
    FILE *plik = fopen("wynik.txt", "w");

    int sm = semafor_init();
    semafor_ustaw(sm);

    //semafor_v(sm, 1);

    for(int i = 0; i < 3; i++)
    {
        char prog[] = "PX";
        char path[] = "./PX";
        prog[1] = '1' + i;
        path[3] = '1' + i;

	    pid_t id = fork();
	    if(id == 0)	//Potmek
	    {
	        int fail = execl(path, prog, NULL);

            if(fail < 0)
            {
                perror("Exel error: ");
            }
        }
    }

    for(int i = 0; i < 3; i ++)
    {
        int potomny, status;
        potomny = wait(&status);
    }

    usun_semafor(sm);
    fclose(plik);
    printf("Koniec programu\n");

    return 0;
}