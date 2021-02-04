#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"
//原生数组类
namespace MyLib
{
    template <typename T>
    class Array: public Object
    {
    protected://protect继承 使得子类可以调用
        T* m_array;
    public:
        virtual bool set(int i,const T&e)
        {
            bool ret=((0<=i)&&(i<length()));//判断条件

            if(ret)
            {
                m_array[i]=e;
            }
            return ret;
        }

        virtual bool get(int i,T&e)const
        {
            bool ret=((0<=i)&&(i<length()));

            if(ret)
            {
                e=m_array[i];
            }

            return ret;
        }
        virtual int length()const=0;//纯虚函数 子类实现
        //数组访问操作符
        T& operator[](int i)//数组重载操作符的实现
        {
            if((0<=i)&&(i<length()))
            {
                return m_array[i];
            }
            else
            {
                THROW_EXCEPTION(indexOutOfBoundsException,"Parameter i is invalid");//访问越界
            }
        }
        T operator[](int i)const
        {
            return(const_cast<Array<T>&>(*this))[i];//强制类型转换去除const属性
        }
    };
}

#endif // ARRAY_H
