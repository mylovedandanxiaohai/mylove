#ifndef QUEUETOSTACK_H
#define QUEUETOSTACK_H

#include "Stack.h"
#include "LinkQueue.h"
//用队列来实现栈的，用队列的先进先出特性实现栈的后进后出的特性
//用队列实现栈需要使用两个队列
namespace MyLib
{
    template <typename T>
    class QueueToStack:public Stack<T>
    {
    protected:
        LinkQueue<T>m_queue1;
        LinkQueue<T>m_queue2;
        LinkQueue<T>* m_in;//入队列
        LinkQueue<T>* m_out;//出队列
//将入队列的前n-1个元素移动出队列
        void move()const
        {
            int n=m_in->length()-1;
            for(int i=0;i<n;i++)
            {
                m_out->add(m_in->front());
                m_in->remove();
            }
        }
//交换的实现
        void swap()
        {
            LinkQueue<T>* temp=NULL;
            temp=m_in;
            m_in=m_out;
            m_out=temp;
        }
    public:
        QueueToStack()
        {
            m_in=&m_queue1;
            m_out=&m_queue2;
        }

        void push(const T &e)
        {
            m_in->add(e);
        }

        void pop()
        {
            if(m_in->length()>0)
            {
                move();
                m_in->remove();
                swap();
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        void clear()
        {
          m_queue1.clear();
          m_queue2.clear();
        }

        T top() const
        {
          if(m_in->length() > 0)
          {
              move();//移动
              return m_in->front();
          }
          else
          {
              THROW_EXCEPTION(InvalidOperationException, "No element...");
          }
        }

        int size()const
        {
          return m_queue1.length() + m_queue2.length();
        }
    };
}

#endif // QUEUETOSTACK_H
