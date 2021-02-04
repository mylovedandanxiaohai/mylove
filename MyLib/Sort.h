#ifndef SORT_H
#define SORT_H

#include "Object.h"

namespace MyLib
{
    class Sort:public Object
    {
    private:
        Sort();//不能产生具体的对象
        Sort(const Sort&);//拷贝构造函数
        Sort& operator =(const Sort&);//赋值操作符重载

        template <typename T>
        static void Swap(T&a,T&b)//静态
        {
            T c(a);
            a=b;
            b=c;
        } 

        template <typename T>
        static void Merge(T src[],T helper[],int begin,int mid,int end)
        {
            int i=begin;
            int j=mid+1;
            int k=begin;

            while((i<=mid)&&(j<=end))
            {
                if(src[i]<src[j])
                {
                    helper[k++]=src[i++];
                }
                else
                {
                    helper[k++]=src[j++];
                }
            }

            while(i<=mid)
            {
                helper[k++]=src[i++];
            }
            while(j<=end)
            {
                helper[k++]=src[j++];
            }

            for(i=begin;i<=end;i++)
            {
                src[i]=helper[i];
            }
        }

        template <typename T>
        static void Merge(T src[],T helper[],int begin,int end)
        {
            if(begin==end)
            {
                return;
            }
            else
            {
                int mid=(begin+end)/2;

                Merge(src,helper,begin,mid);
                Merge(src,helper,mid+1,end);
                Merge(src,helper,begin,mid,end);
            }
        }

        template <typename T>
        static int Partiton(T array[],int begin,int end)
        {
            T pv=array[begin];

            while(begin<end)
            {
                while((begin<end)&&(array[end]>pv))
                {
                    end--;
                }
                Swap(array[begin],array[end]);

                while((begin<end)&&(array[begin]<=pv))
                {
                    begin++;
                }
                Swap(array[begin],array[end]);
            }

            array[begin]=pv;

            return begin;
        }

        template <typename T>
        static void Quick(T array[],int begin,int end)
        {
            if(begin<end)
            {
                int pivot=Partiton(array,begin,end);

                Quick(array,begin,pivot-1);
                Quick(array,pivot+1,end);
            }
        }
    public:
        //选择排序的实现
        template <typename T>
        static void select(T array[],int len)
        {
            for(int i=0;i<len;i++)
            {
                int min=i;//从第i个元素开始

                for(int j=i+1;j<len;j++)//将最小值与剩下的元素进行比较
                {
                    if(array[min]>array[j])
                    {
                        min=j;
                    }
                }
                if(min!=i)//避开不必要的交换  指的是两个值是相等的
                {
                    Swap(array[i],array[min]);

                }
                //Swap(arrar[0],arrar[min]);
            }
         }
         //插入排序的实现
         template <typename T>
         static void insert(T array[],int len)
         {
             for(int i=1;i<len;i++)
             {
                 int k=i;
                 T temp=array[i];
                 for(int j=i-1;(j>=0);j--)//
                 {
                     if(array[j]>temp)//如果array[j]下的值大于temp,将array[j]往后移动一位
                     {
                        array[j+1]=array[j];//位置移动
                        k=j;//记录位置
                     }
                     else
                     {
                         break;
                     }
                 }
                 if(k!=i)//避免相等的赋值交换
                 {
                     array[k]=temp;
                 }
             }
         }

         template <typename T>//冒泡排序
         static void Bubble(T array[],int len)
         {
             bool exchange=true;
             for(int i=0;(i<len)&&exchange;i++)//从后往前的实现
             {
                 exchange=false;

                 for(int j=len-1;j>i;j--)//前面排好序
                 {
                     if(array[j]<array[j-1])
                     {
                        Swap(array[j-1],array[j]);
                     }
                 }
             }
         }

         //将排序序列划分为若干组，在每一组内进行排序，以使整个序列基本有序，然后再对整个序列进行插入排序
         template <typename T>
         static void Shell(T array[],int len)
         {
             int d=len;//d为分组的间隔

             do
             {
                d=d/3+1;//d为增量 d的值在排序的过程中由大到小逐渐缩小，直至最后一趟排序减为1

                for(int i=d;i<len;i+=d)
                {
                    //cout<<i;
                    int k=i;
                    T temp=array[i];
                    for(int j=i-d;j>=0;j-=d)
                    {
                        if(array[j]>temp)
                        {
                           array[j+d]=array[j];
                           k=j;
                           //cout<<k;
                        }
                        else
                        {
                            break;
                        }
                    }
                    if(k!=i)
                    {
                        array[k]=temp;
                    }
                }
             }while(d>1);
         }

         template <typename T>//归并排序的实现
         static void Merge(T array[],int len)
         {
             T* helper=new T[len];//申请的辅助空间

             if(helper!=NULL)
             {
                 Merge(array,helper,0,len-1);
             }
         }

         template <typename T>//快速排序
         static void Quick(T array[],int len)
         {
             Quick(array,0,len-1);
         }
    };
}

#endif // SORT_H
