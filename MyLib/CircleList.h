 #ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace MyLib
{
    template <typename T>
    class CircleList:public LinkList<T>
    {
    protected:
        typedef typename LinkList<T>::Node Node;
        Node* last() const//尾节点
        {
            return this->position(this->m_length-1)->next;//返回尾节点(m_length-1)
        }

        void last_to_first()const//将链表首尾相连
        {
            last()->next=this->m_header.next;//尾节点的next指针指向首节点
        }

        int mod(int i)const
        {
            return (this->m_length==0) ? 0 : ( i % this->m_length);
        }

    public:
        bool insert(const T& e)//重载
        {
            return insert(this->m_length,e);//调用重载的版本
        }

        bool insert(int i,const T& e)
        {
            bool ret=true;

            i=i%(this->m_length+1);//i值取余

            ret=LinkList<T>::insert(i,e);//调用父类的insert来实现子类的insert

            if(ret&&(i==0))
            {
                last_to_first();
            }

            return ret;
        }

        bool remove(int i)
        {
            bool ret= true;

            i= mod(i);//取余的实现

            if(i==0)
            {
                Node *toDel=this->m_header.next;

                if(toDel!=NULL)
                {
                    this->m_header.next=toDel->next;
                    this->m_length--;
                    //链表不为空
                    if(this->m_length>0)
                    {
                        last_to_first();

                        if(this->m_current==toDel)
                        {
                            this->m_current=toDel->next;
                        }
                    }
                    else
                    { //链表为空，置空
                        this->m_header.next=NULL;
                        this->m_current=NULL;
                    }

                    this->destroy(toDel);//在最后一步删除首节点  避免了异常安全
                }
                else
                {
                    ret=false;
                }
            }
            else
            {
                ret=LinkList<T>::remove(i);
            }

            return ret;
        }

        bool set(int i, const T &e)
        {
            i=mod(i);
            return LinkList<T>::set(i,e);//调用父类函数
        }

        T get(int i)const
        {
            i=mod(i);
            return LinkList<T>::get(i);
        }

        T get(int i,const T&e) const
        {
            i=mod(i);
            return LinkList<T>::get(i,e);
        }

        int find(const T &e)const
        {
            int ret=-1;
            Node* slide=this->m_header.next;//指针slide指向首节点
            for(int i=0;i<this->m_length;i++)//slide指针遍历每个元素
            {
                if(slide->value==e)
                {
                    ret=i;
                    break;
                }
                slide=slide->next;
            }

            return ret;
        }

        void clear()
        {
            while(this->m_length>1)
            {
                remove(1);//这里取1的原因是效率更高
            }
            if(this->m_length==1)
            {
                Node* toDel=this->m_header.next;
                this->m_header.next=NULL;
                this->m_length=0;
                this->m_current=NULL;

                this->destroy(toDel);
            }
        }

        bool move(int i, int step)//i表示位置
        {
            i=mod(i);
            return LinkList<T>::move(i,step);
        }

        bool end()
        {
            return (this->m_length==0)||(this->m_current==NULL);
        }

        ~CircleList()//析构函数直接调用clear()函数
        {
            clear();
        }
    };
}

#endif // CIRCLELIST_H
