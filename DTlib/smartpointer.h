#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

namespace DTlib
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
    class SmartPointer//定义的类
    {
    protected:
        T* m_pointer;//创建的成员变量
    public:
        SmartPointer(T* p=NULL)
        {
            m_pointer=p;
        }

        SmartPointer(const SmartPointer<T>& obj)
        {
            m_pointer=obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
        }

        SmartPointer<T>& operator =(const SmartPointer<T>& obj)
        {
            if(this!=obj)
            {
                delete m_pointer;

                m_pointer=obj.m_pointer;

                const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
            }


            return *this;
        }

        //重载指针的特征操作符
        T* operator->()
        {
            return m_pointer;
        }

        T& operator*()
        {
            return *m_pointer;
        }

        bool isNull()
        {
            return (m_pointer==NULL);
        }

        T* get()
        {
            return m_pointer;
        }

        ~SmartPointer()
        {
            delete m_pointer;
        }
    };
}

#endif // SMARTPOINTER_H
