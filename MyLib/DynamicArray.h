#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace MyLib
{
    template <typename T>
    class DynamicArray:public Array<T>
    {
    protected:
        int m_length;
        T* copy(T* array,int len,int newlen)
        {
            T* ret=new T[newlen];

            if(ret!=NULL)
            {
                int size=(len<newlen)?len:newlen;

                for(int i=0;i<size;i++)
                {
                    ret[i]=array[i];
                }
            }

            return ret;
        }

        void update(T* array,int length)
        {
            if(array!=NULL)
            {
                T* temp=this->m_array;

                this->m_array=array;
                this->m_length=length;

                delete [] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEoughMemoryException,"...");
            }
        }
    public:
        DynamicArray(int length)
        {
            this->m_array=new T[length];//堆空间申请内存

            if(this->m_array!=NULL)
            {
                this->m_length=length;//记录当前数组的长度
            }
            else
            {
                THROW_EXCEPTION(NoEoughMemoryException,"No memory to ....");
            }
        }

        DynamicArray(const DynamicArray<T>& obj)
        {
            this->m_array=new T[obj.m_length];//堆空间申请内存

            if(this->m_array!=NULL)
            {
                this->m_length=obj.m_length;

                for(int i=0;i<obj.m_length;i++)//进行拷贝的工作
                {
                    this->m_array[i]=obj.m_array[i];
                }
            }
            else
            {
                THROW_EXCEPTION(NoEoughMemoryException,"No memory to ....");
            }
        }

        DynamicArray<T>& operator=(const DynamicArray<T>& obj)
        {         
            if(this!=&obj)
            {
                T* array=copy(obj.m_array,obj.m_length,obj.m_length);
                update(array,obj.m_length);
            }
        }

        int length() const
        {
            return m_length;
        }

        void resize(int length)
        {
            if(length!=m_length)
            {
                T* array=copy(this->m_array,m_length,length);
                update(array,length);
                /*
                    T* array=new T[length];

                    if(array!=NULL)
                    {
                        int size=(length<m_length)?length:m_length;

                        for(int i=0;i<size;i++)
                        {
                            array[i]=this->m_array[i];
                        }

                        T* temp=this->m_array;

                        this->m_array=array;
                        this->m_length=length;

                        delete [] temp;
                    }
                    else
                    {
                        THROW_EXCEPTION(NoEoughMemoryException,"No memory to...");
                    }
                    */
            }
        }

        ~DynamicArray()
        {
            delete[] this->m_array;
        }
    };
}

#endif // DYNAMICARRAY_H
