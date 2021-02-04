#include <iostream>

using namespace std;
//函数模板的使用
template <typename T>
void Swap(T&a,T&b)
{
    T t=a;
      a=b;
      b=t;
}

template <typename T>//类模板只能显示的调用(指定具体类型),使用具体类型<Type>来定义对象
class op
{
public:
       T process(T v)//此处的T可以在函数的定义中可以为各种类型
       {
           return v*v;
       }
};

int main()
{
    int a=1;
    int b=2;

    Swap(a,b);//自动类型的调用
    cout<<"a="<<a<<" "<<"b="<<b<<endl;

    double c=0.1;
    double d=0.2;

    Swap<double>(c,d);//具体类型的显示调用
    cout<<"c="<<c<<" "<<"d="<<d<<endl;

    op<int>opInt;
    op<double>opDouble;

    cout<<opInt.process(5)<<endl;
    cout<<opDouble.process(0.2)<<endl;

    return 0;
}
