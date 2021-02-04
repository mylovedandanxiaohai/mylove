#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace MyLib
{
    template <typename T,int N>
    class StaticLinkList :public LinkList<T>
    {
    protected:
        typedef typename LinkList<T>::Node Node;

        struct SNode: public Node
        {
            void* operator new(unsigned int size,void* loc)
            {
                (void)size;
                return loc;
            }
        };

        unsigned char m_space[sizeof(SNode)*N];//父类的Node与泛指类型T有关
        int m_use[N];

        void destroy(Node* pn)//归还空间和调用析构函数
        {
            SNode* space=reinterpret_cast<SNode*>(m_space);//,指针运算,指针的强制类型转换
            SNode* psn=dynamic_cast<SNode*>(pn);                          //父类指针转换到子类指针dynamic_cast

            for(int i=0;i<N;i++)
            {
                if(psn==(space+i))
                {
                    m_use[i]=0;
                    psn->~SNode();//调用析构函数
                    break;
                }
            }
        }

        Node* create()
        {
            SNode* ret=NULL;

            for(int i=0;i<N;i++)
            {
                if(!m_use[i])
                {
                    ret=reinterpret_cast<SNode*>(m_space)+i;//分配内存
                    ret=new(ret)SNode();//调用构造函数
                    m_use[i]=1;
                    break;
                }
            }

            return ret;
        }
    public:
        StaticLinkList()
        {
            for(int i=0;i<N;i++)
            {
                m_use[i]=0;//标记可用
            }
        }

        int capacity()
        {
            return N;
        }

        ~StaticLinkList()
        {
            this->clear();
        }
    };
}

#endif // STATICLINKLIST_H
