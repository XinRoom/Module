#include <unistd.h>
#include <stdio.h>

#include "Timer.h"

Timer::Timer()
{
    this->isStart=false;  //��ʼ���ر��̱߳�־
    this->wheel=new time_wheel();
    this->stack_index=0;
    this->timer_count=0;

    ///�����߳�
    pthread_create(&this->pt,NULL,run,(void *)this);
    pthread_detach(this->pt); ///�����߳�Ϊ����̬
}

void *Timer::run(void * arg)
{
    //��̬ת��
    Timer *t=static_cast<Timer *>(arg);

    while(t->isStart==false);
    while(t->isStart!=false)
    {
         sleep(1);
         //��ʱ������
         t->wheel->tick();
         printf("tick\n");
    }
}

//���к�����
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

    ///���û�б�������timer_t
    if(this->stack_index<=0)
    {
        timers[this->timer_count++]=this->wheel->add_timer(timeout,handler);
        r=this->timer_count-1;

    }

    ///����б�������timer_t�����stack��ȡ��������timer_tʹ��
    if(this->stack_index>0)
    {
        int index=stack[this->stack_index-1];
        timers[index]=this->wheel->add_timer(timeout,handler);
        r=index;
        this->stack_index--;

    }

    return r;

}


//ɾ����ʱ��
int Timer::deleteTimer(w_timer_t timer_n)
{
    tw_timer *tw=timers[timer_n]; ///��ȡ��timer

    if(tw!=NULL){
        this->wheel->del_timer(tw); //delete
        //delete tw;
        //tw�Ѿ���tw��delete��
        tw=NULL;
        stack[this->stack_index++]=timer_n; //��������timer_t ��ŵ���������
        return 0;
    }

    return -1;
}


Timer::~Timer()
{
    delete [] this->timers;
    delete this->wheel;
}







