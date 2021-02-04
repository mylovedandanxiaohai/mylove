#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"
//根据存储空间的分配方式可以分为使用原生数组实现的静态队列和使用动态分配的堆空间实现的动态队列。
//静态队列的实现要点如下：
//A、类模板实现
//B、使用原生数组作为队列的存储空间
//C、使用模板参数决定队列的容量大小
namespace MyLib
{
    template <typename T,int N>
    class StaticQueue:public Queue<T>
    {
    protected:
        T m_space[N];//队列的存储空间
        int m_front;//队头元素的标识
        int m_rear;//队尾元素的标识
        int m_length;//队列长度
    public:
        StaticQueue()
        {//初始化成员为0
            m_length=0;
            m_front=0;
            m_rear=0;
            //m_space[N]=0;
        }

        int capacity()const
        {
            return N;
        }

        void add(const T&e)
        {
            if(m_length<N)
            {
                m_space[m_rear]=e;
                m_rear=(m_rear+1)%N;//取余为了循环计数
                m_length++;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        void remove()
        {
            if(m_length>0)
            {
                m_front=(m_front+1)%N;
                m_length--;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        T front()const
        {
            if(m_length>0)
            {
                return m_space[m_front];
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        void clear()
        {
            m_front=0;
            m_rear=0;
            m_length=0;
        }

        int length()const
        {
            return m_length;
        }
    };
}

#endif // STATICQUEUE_H
