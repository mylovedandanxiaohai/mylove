 #ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace MyLib
{
    template <typename T>
    class SeqList:public List<T>
    {
    protected:
        T* m_array;//存储空间
        int m_length;//当前长度
    public://线性表的顺序存储结构的一些操作
        /*插入操作
         1.判断目标是否合法
         2.将目标位置之后的所有元素后移一个位置
         3.将新元素插入目标位置
         3.线性表长度加1
        */
        bool insert(int i,const T&e)
        {
            bool ret=((0<=i)&&(i<=m_length));//判断条件

            ret=ret&&((m_length+1)<capacity());//判断条件
            if(ret)
            {
                for(int p=m_length-1;p>=i;p--)//遍历插入点后的元素,从后往前
                {
                    m_array[p+1]=m_array[p];//插入点后的元素与它后面的元素就行位置交换
                }
                m_array[i]=e;//将元素插入
                m_length++;//长度加1
            }

            return ret;
        }

        bool insert(const T&e)//在尾部插入数据
        {
            return insert(m_length,e);
        }

        /*删除操作
         1.判断目标是否合法
         2.将目标位置后的所有元素前移一个位置
         3.线性表长度减1
        */
        bool remove(int i)
        {
            bool ret=((0<=i)&&(i<=m_length));

            if(ret)
            {
                for(int p=i;p<m_length;p++)//在删除点往后遍历
                {
                    m_array[p]=m_array[p+1];
                }
                m_length--;
            }
            return ret;
        }

        bool set(int i,const T&e)
        {
            bool ret=((0<=i)&&(i<=m_length));

            if(ret)
            {
                m_array[i]=e;
            }
            return ret;
        }

        bool get(int i,T&e) const
        {
            bool ret=((0<=i)&&(i<=m_length));

            if(ret)
            {
                e=m_array[i];
            }
            return ret;
        }

        int find(const T&e)const
        {
            int ret=-1;

            for(int i=0;i<m_length;i++)
            {
                if(m_array[i]=e)
                {
                    ret=i;
                    break;
                }
            }

            return ret;
        }

        int length()const
        {
            return m_length;
        }

        void clear()
        {
            m_length=0;
        }

        //数组的访问
        T& operator[](int i)//数组操作符的重载
        {
           if((0<=i)&&(i<=m_length))
           {
               return m_array[i];
           }
           else
           {
               THROW_EXCEPTION(indexOutOfBoundsException,"Parameter i is invaild...");//i不合法，越界操作异常
           }
        }

        T operator [](int i)const
        {
            //去除当前对象的const属性
            return (const_cast<SeqList<T>&>(*this))[i];
        }

        virtual int capacity()const=0;//纯虚h函数，由子类重写

    };
}

#endif // SEQLIST_H
