#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"
namespace MyLib
{
    /*智能指针的实现(智能指针只能指向单个变量或者单个对象)
        1.指针生命周期结束时主动释放空间
        2.一片堆空间最多只能由一个指针标识
        3.杜绝指针运算和指针比较

        设计方案
        1.通过类模板描述指针的行为(能够定义不同类型的指针对象)
        2.重载指针特征操作符(->和*)(利用对象模拟原生指针的行为)
    */
    template<typename T>//创建的指针可以指向任意的类型
    class SmartPointer:public Pointer<T>//定义的类
    {
    public:
        SmartPointer(T* p=NULL):Pointer<T>(p)
        {

        }

        SmartPointer(const SmartPointer<T>& obj)//拷贝构造函数
        {
            this->m_pointer=obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
        }

        SmartPointer<T>& operator =(const SmartPointer<T>& obj)//赋值操作符重载
        {
            if(this!=obj)
            {
                T* p=this->m_pointer;

                //delete m_pointer;

                this->m_pointer=obj.m_pointer;

                const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;

                delete p;
            }


            return *this;
        }

        ~SmartPointer()
        {
            delete this->m_pointer;
        }
    };
}

#endif // SMARTPOINTER_H
