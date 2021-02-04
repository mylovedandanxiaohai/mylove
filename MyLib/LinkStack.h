#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "LinkList.h"
//链式栈的实现要点：
//A、类模板实现，继承自抽象父类Stack
//B、内部组合使用LinkList类，实现栈的链式存储
//C、只在单链表成员对象的头部进行操作
namespace MyLib
{
    template <typename T>
    class LinkStack:public Stack<T>
    {
    protected:
        LinkList<T>m_list;
    public:
        void push(const T&e)
        {
            m_list.insert(0,e);
        }

        void pop()
        {
            if(m_list.length()>0)
            {
                m_list.remove(0);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        T top() const
        {
            if(m_list.length()>0)
            {
                return m_list.get(0);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        void clear()
        {
            m_list.clear();
        }

        int size() const
        {
            return m_list.length();
        }
    };
}

#endif // LINKSTACK_H
