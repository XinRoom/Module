#include <stdio.h>
#include <errno.h>
#include "SemOpt.h"
///�����ź�����ħ��key���ź����ĳ�ʼֵvalue;

sem_t CreateSem(key_t  key,int value){

    union semun sem;

    sem_t semid;
    sem.val=value;

    semid=semget(key,1,IPC_CREAT|0666);

    if(-1 == semid){
        printf("create semaphore error\n");
        return -1;
    }

    semctl(semid,0,SETVAL,sem);

    return semid;
}

/*****************
struct sembuf{
    ushort sem_num;  ///�ź����ı��
    short sem_op;  ///�ź����Ĳ���
    short sem_flg; ///�ź���������־
};
*******************/

int Sem_P(sem_t semid){
       struct sembuf sops={0,+1,IPC_NOWAIT};
       return (semop(semid,&sops,1));
}

int Sem_V(sem_t semid){
    struct sembuf sops={0,-1,IPC_NOWAIT};
    return (semop(semid,&sops,1));
}


void SetvalueSem(sem_t semid,int value){
    union semun sem;
    sem.val=value;
    semctl(semid,0,SETVAL,sem);
}


int GetvalueSem(sem_t semid){
    union semun sem;
    return semctl(semid,0,GETVAL,sem);
}


void DestroySem(sem_t semid){
    union semun sem;
    sem.val=0;
    semctl(semid,0,IPC_RMID,sem);
}





