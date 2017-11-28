#ifndef __SEMOPT_H_
#define __SEMOPT_H_

/********************
union semun{            ///�ź������������Ͻṹ
    int val;
    struct semid_ds *buf;  //
    unsigned short *array;   //��������
    struct seminfo *__buf;   //�ź����ڲ����ݽṹ
}
**********************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


typedef int sem_t;

union semun{
    int  val;
    struct  semid_ds *buf;
    unsigned short *array;
}arg;

///�����ź�����ħ��key���ź����ĳ�ʼֵvalue;
//�����ź���
sem_t CreateSem(key_t  key,int value);

/*****************
struct sembuf{
    ushort sem_num;  ///�ź����ı��
    short sem_op;  ///�ź����Ĳ���
    short sem_flg; ///�ź���������־
};
*******************/

int Sem_P(sem_t semid);

int Sem_V(sem_t semid);


void SetvalueSem(sem_t semid,int value);


int  GetvalueSem(sem_t semid);


void DestroySem(sem_t semid);


#endif
