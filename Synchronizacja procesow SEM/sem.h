#ifndef SEM_H_
#define SEM_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>

int semafor_init(key_t klucz)
{
    int semafor = semget(klucz, 3, IPC_CREAT | 0600);

    return semafor;
}

void semafor_ustaw(int id)
{
    for (int i = 0; i < 3; i++)
    {
        int ustaw_sem;
        ustaw_sem=semctl(id, i, SETVAL, 0);
        if (ustaw_sem==-1)
        {
            printf("Nie mozna ustawic semafora.\n");
            exit(EXIT_FAILURE);
        }
    }
}

void status(int id)
{
    for(int i = 0; i < 3; i++)
        printf("War %d\n", semctl(id, i, GETVAL));
}

void semafor_p(int id, int sem)
{
    int zmien_sem;
    struct sembuf bufor_sem;
    bufor_sem.sem_num = sem;
    bufor_sem.sem_op = -1;
    bufor_sem.sem_flg=SEM_UNDO;
    zmien_sem=semop(id,&bufor_sem,1);
    if (zmien_sem==-1)
    {
        printf("Nie moglem zamknac semafora.\n");
        exit(EXIT_FAILURE);
    }
}

void semafor_v(int id, int sem)
{
    int zmien_sem;
    struct sembuf bufor_sem;
    bufor_sem.sem_num = sem;
    bufor_sem.sem_op = 1;
    bufor_sem.sem_flg=SEM_UNDO;
    zmien_sem=semop(id,&bufor_sem,1);

    if (zmien_sem==-1)
    {
        printf("Nie moglem otworzyc semafora.\n");
        exit(EXIT_FAILURE);
    }      
}

void usun_semafor(int id)
{
    int sem;
    sem=semctl(id,3,IPC_RMID);
    if (sem==-1)
    {
        printf("Nie mozna usunac semafora.\n");
        exit(EXIT_FAILURE);
    }
}

#endif 