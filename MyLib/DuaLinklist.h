#ifndef DUALINKLIST_H
#define DUALINKLIST_H

#include "List.h"
#include "Exception.h"

namespace MyLib
{
    template <typename T>
    class DuaLinkList:public List<T>
    {
    protected:
        struct Node :public Object
        {
            T value;//数据域   保存数据的值
            Node* next;//指针域 指向后继节点的指针
            Node* pre;//指向当前结点的前驱节点
        };

        mutable struct:public Object//没有类型名的结构
        {
            char reserved[sizeof(T)];
            Node* next;
            Node* pre;
        }  m_header;//头节点  辅助定位元素
        int m_length;
        int m_step;
        Node* m_current;

        Node* position(int i) const//程序优化
        {
            Node* ret=reinterpret_cast<Node*>(&m_header);//reinterpret_cast强制类型转换

            for(int p=0;p<i;p++)
            {
                ret=ret->next;
            }

            return ret;
        }

        virtual Node* create()
        {
            return new Node();
        }

        virtual void destroy(Node* pn)
        {
            delete pn;
        }

    public:
        DuaLinkList()
        {
            m_header.next=NULL;
            m_header.pre=NULL;
            m_length=0;
            m_step=1;
            m_current=NULL;
        }

        bool insert(const T&e)
        {
           return insert(m_length,e);
        }

        bool insert(int i,const T&e)//i表示插入的位置，e表示插入的数据
        {
            bool ret=((0<=i)&&(i<= m_length));//m_length表示链表的长度

            if(ret)
            {
                Node* node=create();

                if(node!=NULL)
                {
                    Node* current=position(i);//定位位置
                    Node* next=current->next;//表示插入的节点的后继节点

                    node->value=e;
                    node->next=next;
                    current->next=node;
                    if(current!=reinterpret_cast<Node*>(&m_header))
                    {
                        node->pre=current;
                    }
                    else
                    {
                        node->pre=NULL;
                    }

                    if(next!=NULL)
                    {
                        next->pre=node;
                    }

                    m_length++;
                }
                else
                {
                    THROW_EXCEPTION(NoEoughMemoryException,"No ...");
                }
            }


            return ret;
        }

        bool remove(int i)
        {
            bool ret=((0<=i)&&(i<m_length));

            if(ret)
            {
                Node* current=position(i);
                Node* toDel=current->next;
                Node* next=toDel->next;

                if(m_current==toDel)
                {
                    m_current=next;
                }

                current->next=next;
                if(next!=NULL)
                {
                    next->pre=toDel->pre;
                }

                m_length--;

                destroy(toDel);

                //m_length--;
            }

            return ret;
        }

        bool set(int i,const T&e)
        {
             bool ret=((0<=i)&&(i<m_length));

             if(ret)
             {
                 position(i)->next->value=e;
             }

             return ret;
        }

        int find(const T&e) const
        {
            int ret=-1;
            int i=0;

            Node* node=m_header.next;

            while(node)
            {
                if(node->value==e)
                {
                    ret=i;
                    break;
                }
                else
                {
                    node=node->next;
                    i++;
                }
            }
            return ret;
        }

        virtual T get(int i)const
        {
            T ret;

            if(get(i,ret))
            {
                return ret;
            }
            else
            {
                THROW_EXCEPTION(indexOutOfBoundsException,"...");
            }

            return ret;
        }

        bool get(int i,T&e)const
        {
            bool ret=((0<=i)&&(i<m_length));

            if(ret)
            {

                e=position(i)->next->value;
            }

            return ret;
        }

        int length()const
        {
            return m_length;
        }

        void clear()
        {
            while(m_length>0)
            {
                remove(0);
            }
        }

        virtual bool move(int i,int step=-1)
        {
            bool ret= (0<=i)&&(i<m_length)&&(step>0);

            if(ret)
            {
                m_current=position(i)->next;
                m_step=step;
            }

            return ret;
        }

        virtual bool end()
        {
            return (m_current==NULL);
        }

        virtual T current()
        {
            if(!end())
            {
                return m_current->value;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        virtual bool next()
        {
            int i=0;

            while((i<m_step)&& !end())
            {
                m_current=m_current->next;
                i++;
            }
            return (i==m_step);
        }

        virtual bool pre()
        {
            int i=0;

            while((i<m_step)&& !end())
            {
                m_current=m_current->pre;
                i++;
            }
            return (i==m_step);
        }

        ~DuaLinkList()
        {
            clear();
        }
    };
}

#endif // DUALINKLIST_H
