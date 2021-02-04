#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace DTlib
{
    class Exception
    {
    protected:
        char* m_message;
        char* m_location;

        void init(const char* message,const char *file,int line);
    public:
        Exception(const char* message);
        Exception(const char *file,int line);
        Exception(const char* message,const char *file,int line);

        Exception(const Exception& e);
        Exception& operator=(const Exception& e);

        virtual const char* message()const;
        virtual const char* location()const;

        virtual ~Exception()=0;
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

}
#endif // EXCEPTION_H
