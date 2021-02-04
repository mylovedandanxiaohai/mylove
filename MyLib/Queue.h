#ifndef QUEUE_H
#define QUEUE_H

#include "Object.h"
//队列的抽象父类
namespace MyLib
{
    template <typename T>
    class Queue:public Object
    {
    public:
        virtual void add(const T&e)=0;//进队列的操作
        virtual void remove()=0;//出队列
        virtual T front()const=0;//获取队头元素
        virtual void clear()=0;//情况队列
        virtual int length()const=0;//队列长度
    };
}

#endif // QUEUE_H
