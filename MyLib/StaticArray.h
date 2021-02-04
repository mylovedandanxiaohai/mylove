#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"
//设计要点
//1.封装原生数组
//2.使用模板参数决定数组大小
//3.实现函数返回数组长度
//4.拷贝构造和赋值操作
namespace MyLib
{
    template <typename T,int N>
    class StaticArray :public Array<T>
    {
    protected:
        T m_space[N];//原生数组
    public:
        StaticArray()
        {
            this->m_array=m_space;//父类的m_array指向子类的原生数组
        }

        StaticArray(const StaticArray<T,N>& obj)
        {
            this->m_array=m_space;
            for(int i=0;i<N;i++)//用于具体赋值数组元素的值
            {
                m_space[i]=obj.m_space[i];
            }
        }

        StaticArray<T,N>& operator=(const StaticArray<T,N>& obj)
        {
            if(this!=&obj)//自赋值情况的避免
            {
                for(int i=0;i<N;i++)
                {
                    m_space[i]=obj.m_space[i];
                }
            }

            return *this;
        }

        int length() const
        {
            return N;
        }
    };
}

#endif // STATICARRAY_H
