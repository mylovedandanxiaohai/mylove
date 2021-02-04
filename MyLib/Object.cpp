#include "Object.h"
#include <cstdlib>
#include <iostream>

using namespace std;
//定义的动态内存申请的行为，提高代码的移植性
//在堆中创建Object子类的对象，失败时返回NULL值
namespace MyLib
{
    void* Object::operator new(unsigned int size)throw()
    {
        //cout<<"void* Object::operator new:"<<size<<endl;//打印的size的有一个指向虚函数的整数指针的值为4
        return malloc(size);
    }

    void Object::operator delete(void* p)
    {
        //cout<<"void Object::operator delete:"<<p<<endl;
        free(p);
    }

    void* Object::operator new[](unsigned int size)throw()
    {
        return malloc(size);
    }

    void Object::operator delete[](void* p)
    {
        free(p);
    }

    Object:: ~Object()
    {

    }
}

