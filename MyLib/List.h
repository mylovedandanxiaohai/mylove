#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace MyLib
{
//List抽象类
    template <typename T>
    class List:public Object
    {
    protected:
        List(const List&);
        List& operator=(const List&);//避免赋值操作
    public:
        List(){}
        virtual bool insert(const T&e)=0;//链表的插入
        virtual bool insert(int i,const T&e)=0;//重载版本
        virtual bool remove(int i)=0;//链表的删除
        virtual bool set(int i,const T&e)=0;//
        virtual int find(const T&e)const=0;//查找指定的元素
        virtual bool get(int i,T&e)const=0;
        //virtual bool current();
        virtual int length()const=0;
        virtual void clear()=0;
    };
}

#endif // LIST_H
