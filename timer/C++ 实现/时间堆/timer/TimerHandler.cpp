#include "TimerHandler.h"

TimerHandler::TimerHandler(){
     this->data=NULL;
}

///���ö�ʱ������ʱ�����к�����Ҫ������
void TimerHandler::setData(void *arg){
    this->data=arg;
}

///��ȡ����
void* TimerHandler::getData(){
     return this->data;
}

TimerHandler::~TimerHandler(){

}

