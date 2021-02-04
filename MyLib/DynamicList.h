#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
/*
   DynamicList通过动态内存申请定义顺序存储空间
   DynamicList支持动态重置顺序存储空间的大小
 */
namespace MyLib
{
    template <typename T>
    class DynamicList:public SeqList<T>
    {
    protected:
        int m_capacity;//记录顺序存储空间的大小
    public:
        DynamicList(int capacity)//构造函数，申请空间
        {
            this->m_array=new T[capacity];
            if(this->m_array!=NULL)
            {
                this->m_length=0;
                this->m_capacity=capacity;
            }
            else
            {
                THROW_EXCEPTION(NoEoughMemoryException,"error");
            }
        }
        int capacity()const
        {
            return m_capacity;
        }
        /*重新设置顺序存储空间额度大小*/
        void resize(int capacity)
        {
            if(capacity!=m_capacity)//不等于原来的空间
            {
                T* array=new T[capacity];//申请空间
                if(array!=NULL)
                {
                    int length=(this->m_length<capacity ? this->m_length:capacity);
                    for(int i=0;i<length;i++)//此处的循环可以保存resize之前的元素
                    {
                        array[i]=this->m_array[i];
                    }

                    T* temp=this->m_array;//局部指针变量

                    this->m_array=array;
                    this->m_length=length;
                    this->m_capacity=capacity;

                    delete [] temp;
                }
                else
                {
                     THROW_EXCEPTION(NoEoughMemoryException,"error");
                }
            }
        }
        ~DynamicList()//归还空间
        {
            delete[]this->m_array;
        }
    };
}

#endif // DYNAMICLIST_H
