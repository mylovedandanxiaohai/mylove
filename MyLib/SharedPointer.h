#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include <cstdlib>
#include "Exception.h"
//类模板
//通过计数机制(ref)标识堆内存
//堆内存被指向时:ref++
//指针被置空时:ref--
//ref==时:释放堆内存
namespace MyLib
{
    template<typename T>
    class SharedPointer :public Pointer<T>
    {
    protected:
        int* m_ref;

        void assign(const SharedPointer<T>& obj)
        {//计数机制
            //m_pointer继承自父类
            this->m_ref=obj.m_ref;
            this->m_pointer=obj.m_pointer;

            if(this->m_ref)
            {
                (*this->m_ref)++;
            }
        }
    public:
        SharedPointer(T* p=NULL):m_ref(NULL)
        {
            if(p)
            {
                this->m_ref=static_cast<int*>(std::malloc(sizeof(int)));//在堆空间申请一个四个字节
                if(this->m_ref)//内存申请成功的情况下的操作
                {
                    *(this->m_ref)=1;
                    this->m_pointer=p;
                }
                else
                {
                    THROW_EXCEPTION(NoEoughMemoryException,"...");
                }
            }
        }

        SharedPointer(const SharedPointer<T>& obj):Pointer<T>(NULL)
        {
            //都指向了堆空间
            assign(obj);
        }

        SharedPointer<T>& operator=(const SharedPointer<T>& obj)
        {
            if(this!=&obj)//避免自赋值
            {
                clear();//在进行赋值之前  将当前的智能指针对象置空

                assign(obj);
            }

            return *this;
        }

        void clear()
        {
            T* toDel=this->m_pointer;
            int* ref=this->m_ref;

            this->m_pointer=NULL;
            this->m_ref=NULL;

            if(ref)
            {
                (*ref)--;

                if(*ref==0)
                {
                    free(ref);

                    delete toDel;
                }
            }
        }

        ~SharedPointer()
        {
            clear();
        }
    };

    template <typename T>
    bool operator == (const SharedPointer<T>& l,const SharedPointer<T>& r )
    {
        return (l.get()==r.get());
    }

    template <typename T>
    bool operator != (const SharedPointer<T>& l,const SharedPointer<T>& r )
    {
        return !(l==r);
    }
}

#endif // SHAREDPOINTER_H
