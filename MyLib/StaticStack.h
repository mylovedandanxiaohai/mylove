#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace MyLib
{
    template<typename T,int N>
    class StaticStack: public Stack<T>
    {
    protected:
        T m_space[N];//栈存储空间
        int m_top;//栈顶元素标识
        int m_size;//表示当前栈里面的数据个数
    public:
        StaticStack()//构造函数初始化成员
        {
            m_top=-1;
            m_size=0;
        }

        int capacity()const
        {
            return N;//返回最大存储量
        }

        void push(const T &e)
        {//入栈的操作
            if(m_size<N)
            {
                m_space[m_top+1]=e;
                m_top++;
                m_size++;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        void pop()
        {
            if(m_size>0)
            {//出栈的操作
                m_top--;
                m_size--;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        T top() const
        {
            if(m_size>0)
            {
                return m_space[m_top];
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        void clear()
        {
            m_top=-1;
            m_size=0;
        }

        int size()const
        {
            return m_size;
        }
    };
}

#endif // STATICSTACK_H
