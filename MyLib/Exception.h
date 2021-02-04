#ifndef EXCEPTION_H
#define EXCEPTION_H
/*
   异常的类型可以是自定义类类型
   对于类类型异常的匹配依旧是至上而下严格匹配
   
   一般而言
      匹配子类异常的catch放在上部
      匹配父类异常的catch放在下部
 */
#include "Object.h"

namespace MyLib
{
//定义宏THROW_EXCEPTION，抛出异常时直接写异常类型及异常信息即可
#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

    class Exception:public Object
    {
    protected:
        char* m_message;//异常的信息
        char* m_location;//异常的位置

        void init(const char* message,const char *file,int line);
    public:
        Exception(const char* message);
        Exception(const char *file,int line);
        Exception(const char* message,const char *file,int line);

        Exception(const Exception& e);
        Exception& operator=(const Exception& e);

        virtual const char* message()const;
        virtual const char* location()const;

         virtual ~Exception();//纯虚函数
    };

    class ArithmeticException : public  Exception
    {
    public:
        ArithmeticException():Exception(0){}
        ArithmeticException(const char* message):Exception(message){}
        ArithmeticException(const char* file,int line):Exception(file,line){}
        ArithmeticException(const char*message,const char*file,int line):Exception(message,file,line){}

        ArithmeticException(const ArithmeticException& e):Exception(e){}//拷贝构造函数

        ArithmeticException&operator =(const ArithmeticException& e)
        {
            Exception::operator =(e);
            return *this;
        }
    };

    class NullPointerException : public Exception
    {
    public:
        NullPointerException():Exception(0){}
        NullPointerException(const char* message):Exception(message){}
        NullPointerException(const char* file,int line):Exception(file,line){}
        NullPointerException(const char*message,const char*file,int line):Exception(message,file,line){}

        NullPointerException(const NullPointerException& e):Exception(e){}//拷贝构造函数

        NullPointerException&operator =(const NullPointerException& e)
        {
            Exception::operator =(e);
            return *this;
        }
    };

    class indexOutOfBoundsException : public Exception
    {
    public:
        indexOutOfBoundsException():Exception(0){}
        indexOutOfBoundsException(const char* message):Exception(message){}
        indexOutOfBoundsException(const char* file,int line):Exception(file,line){}
        indexOutOfBoundsException(const char*message,const char*file,int line):Exception(message,file,line){}

        indexOutOfBoundsException(const indexOutOfBoundsException& e):Exception(e){}//拷贝构造函数

        indexOutOfBoundsException&operator =(const indexOutOfBoundsException& e)
        {
            Exception::operator =(e);
            return *this;
        }
    };

    class NoEoughMemoryException : public Exception
    {
    public:
        NoEoughMemoryException():Exception(0){}
        NoEoughMemoryException(const char* message):Exception(message){}
        NoEoughMemoryException(const char* file,int line):Exception(file,line){}
        NoEoughMemoryException(const char*message,const char*file,int line):Exception(message,file,line){}

        NoEoughMemoryException(const NoEoughMemoryException& e):Exception(e){}//拷贝构造函数

        NoEoughMemoryException&operator =(const NoEoughMemoryException& e)
        {
            Exception::operator =(e);
            return *this;
        }
    };

    class InvalidOperationException : public Exception
    {
    public:
        InvalidOperationException():Exception(0){}
        InvalidOperationException(const char* message):Exception(message){}
        InvalidOperationException(const char* file,int line):Exception(file,line){}
        InvalidOperationException(const char*message,const char*file,int line):Exception(message,file,line){}

        InvalidOperationException(const InvalidOperationException& e):Exception(e){}//拷贝构造函数

        InvalidOperationException&operator =(const InvalidOperationException& e)
        {
            Exception::operator =(e);
            return *this;
        }
    };

    class InvalidParameterException : public Exception
    {
    public:
        InvalidParameterException():Exception(0){}
        InvalidParameterException(const char* message):Exception(message){}
        InvalidParameterException(const char* file,int line):Exception(file,line){}
        InvalidParameterException(const char*message,const char*file,int line):Exception(message,file,line){}

        InvalidParameterException(const InvalidParameterException& e):Exception(e){}//拷贝构造函数

        InvalidParameterException&operator =(const InvalidParameterException& e)
        {
            Exception::operator =(e);
            return *this;
        }
    };
}
#endif // EXCEPTION_H
