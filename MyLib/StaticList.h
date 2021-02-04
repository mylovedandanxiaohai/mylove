#ifndef STATICLIST_H
#define STATICLIST_H

#include "SeqList.h"

//使用原生数组作为顺序存储空间，使用模板参数决定数组大小
namespace MyLib
{
    template <typename T,int N>
    class StaticList :public SeqList<T>
    {
    protected:
        T m_space[N];//顺序存储空间，N为模板参数
    public:
        StaticList() //指定父类成员的具体值
        {
            this->m_array=m_space;//父类指针指向子类的数组
            this->m_length=0;//初始值
        }
        int capacity() const
        {
            return N;
        }
    };
}

#endif // STATICLIST_H
