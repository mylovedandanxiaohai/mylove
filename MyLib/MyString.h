#ifndef MYSTRING_H
#define MYSTRING_H

#include "Object.h"
//字符串类的实现
namespace MyLib
{
    class String:public Object
    {
    protected:
        char* m_str;
        int m_length;

        void init(const char* s);
        bool equal(const char*l,const char* r,int len)const;

        static int* make_pmt(const char* p);
        static int kmp(const char*s,const char* p);
    public:
        String();

        String(char c);
        String(const char* s);
        String(const String& s);

        int length()const;
        const char* str()const;
        //各种操作符的重载,访问指定下标的字符
        char& operator [](int i);
        char operator [](int i)const;

        bool startWith(const char*s)const;//判断是否以哪个字符串开头或者结束
        bool startWith(const String&s)const;
        bool endOf(const char*s)const;
        bool endOf(const String&s)const;
        String& insert(int i,const char* s);//字符串的插入
        String& insert(int i,const String& s);
        String& trim();//去除字符串两端的空白

        int indexof(const char*s)const;//子串的查找
        int indexof(const String &s) const;

        String& remove(int i,int len);//删除指定下标指定长度的字符串
        String& remove(const char*s);
        String& remove(const String&s);

        String& replace(const char* t,const char* s);//字符串的替换
        String& replace(const String& t,const char* s);
        String& replace(const char* t,const String& s);
        String& replace(const String& t,const String& s);

        String sub(int i,int len)const;

        bool operator ==(const String& s)const;
        bool operator ==(const char* s)const;
        bool operator !=(const String& s)const;
        bool operator !=(const char* s)const;
        bool operator >(const String& s)const;
        bool operator >(const char* s)const;
        bool operator <(const String& s)const;
        bool operator <(const char* s)const;
        bool operator >=(const String& s)const;
        bool operator >=(const char* s)const;
        bool operator <=(const String& s)const;
        bool operator <=(const char* s)const;

        String operator +(const String& s)const;
        String operator +(const char* s)const;
        String& operator +=(const String& s);
        String& operator +=(const char* s);


        String operator -(const String& s)const;
        String operator -(const char* s)const;
        String& operator -=(const String& s);
        String& operator -=(const char* s);

        String& operator =(const String& s);
        String& operator =(const char* s);
        String& operator =(char c);


        ~String();
    };
}

#endif // MYSTRING_H
