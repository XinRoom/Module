#include <unistd.h>
#include <stdio.h>
#include "Timer.h"

Timer::Timer(int count=10)
{
    this->isStart=false;  //��ʼ���ر��̱߳�־
    this->heap=new time_heap(count);
    this->stack_index=0;
    this->timer_count=0;

    ///�����߳�
    pthread_create(&this->pt,NULL,run,(void *)this);
    pthread_detach(this->pt); ///�����߳�Ϊ����̬
    this->heap=new time_heap(10);
}

void *Timer::run(void * arg)
{
    Timer *t=static_cast<Timer *>(arg);

    while(t->isStart==false);
    while(t->isStart!=false)
    {
         sleep(1);
         //��ʱ������
         t->heap->tick();
         printf("tick\n");
    }
}


void Timer::start()
{
    this->isStart=true;
}


void Timer::stop()
{
    this->isStart=false;
}


///��Ӷ�ʱ��
w_timer_t Timer::addTimer(int timeout,TimerHandler *handler)
{
    w_timer_t r=-1;
    heap_timer *htimer=new heap_timer(timeout);
    htimer->handler=handler;

    ///���û�б�������timer_t
    if(this->stack_index<=0)
    {
        this->heap->add_timer(htimer);
        timers[this->timer_count++]=htimer;
        r=this->timer_count-1;

    }

    ///����б�������timer_t�����stack��ȡ��������timer_tʹ��
    if(this->stack_index>0)
    {
        int index=stack[this->stack_index-1];
        this->heap->add_timer(htimer);
        timers[index]=htimer;
        r=index;
        this->stack_index--;

    }

    return r;

}


//ɾ����ʱ��
int Timer::deleteTimer(w_timer_t timer_n)
{
    heap_timer *ht=timers[timer_n]; ///��ȡ��timer

    if(ht!=NULL){
        this->heap->del_timer(ht); //delete
        //delete tw;
        //tw�Ѿ���tw��delete��
        ht->handler=NULL;
        ht=NULL;
        stack[this->stack_index++]=timer_n; //��������timer_t ��ŵ���������
        return 0;
    }

    return -1;
}


Timer::~Timer()
{
    delete [] this->timers;
    delete this->heap;

}







