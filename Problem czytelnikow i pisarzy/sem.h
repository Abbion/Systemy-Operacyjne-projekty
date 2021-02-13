#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>

int semafor_init(int sem_Num)
{
    key_t klucz = ftok(".", 'B');
    if(klucz == -1)
    {
        printf("Blad podczas tworzenia klucza\n");
        exit(EXIT_FAILURE);
    }

    int semafor = semget(klucz, sem_Num, IPC_CREAT | 0600);
    if(semafor == -1)
    {
        perror("Blad podczas uzsykiwania dostepu do semafora: ");
        exit(EXIT_FAILURE);
    }

    return semafor;
}

int semafor_sprawdz(int sem_Num)
{
    key_t klucz = ftok(".", 'B');
    return semget(klucz, sem_Num, IPC_CREAT | IPC_EXCL | 0600);
}

void semafor_ustaw(int id, int val, int count)
{
    for (int i = 0; i < count; i++)
    {
        int ustaw_sem;
        ustaw_sem=semctl(id, i, SETVAL, val);
        if (ustaw_sem==-1)
        {
            perror("Nie mozna ustawic semafora: ");
            exit(EXIT_FAILURE);
        }
    }
}

void semafor_p(int id, int sem)
{
    int zmien_sem;
    struct sembuf bufor_sem;
    bufor_sem.sem_num = sem;
    bufor_sem.sem_op = -1;
    bufor_sem.sem_flg=0;
    zmien_sem=semop(id,&bufor_sem,1);
    if (zmien_sem==-1)
    {
        if(errno == EINTR)
        {
            perror("Przerwanie podczas zamykania: ");
            printf("Ponawiam probe zamkniecia...\n");
            semafor_p(id, sem);
        }

        else
        {
            perror("Nie moglem zamknac semafora: ");
            exit(EXIT_FAILURE);
        }
    }
}

void semafor_v(int id, int sem)
{
    int zmien_sem;
    struct sembuf bufor_sem;
    bufor_sem.sem_num = sem;
    bufor_sem.sem_op = 1;
    bufor_sem.sem_flg=0;
    zmien_sem=semop(id,&bufor_sem,1);

    if (zmien_sem==-1)
    {
        if(errno == EAGAIN)
        {
            perror("Blad zmienna errno: ");
            perror("Ponawiam probe otwarcia...\n");
            semafor_v(id, sem);
        }

        if(errno == EINTR)
        {
            perror("Przerwanie podczas otwierania: ");
            printf("Ponawiam probe otwarcia...\n");
            semafor_p(id, sem);
        }

        else
        {
            perror("Nie moglem otworzyc semafora: ");
            exit(EXIT_FAILURE);   
        }
    }      
}

void usun_semafor(int id)
{
    int sem;
    sem=semctl(id,0,IPC_RMID);
    if (sem==-1)
    {
        perror("Nie mozna usunac semafora: ");
        exit(EXIT_FAILURE);
    }
}
