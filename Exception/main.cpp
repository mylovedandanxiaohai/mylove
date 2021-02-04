#include <iostream>

double divide(double a,double b)
{
    const double delta=0.000000001;
    double ret=0;

     if( !((-delta < b) && (b < delta)) )
     {
         ret=a/b;
     }
     else
     {
         throw 0;//throw抛出异常必须被catch处理
     }

     return ret;
}

using namespace std;

int main()
{
    cout<<"int main() begin"<<endl;

    try
    {
        double c=divide(1,0);//

        cout<<"c="<<c<<endl;
    }
    catch(...)//此处的catch(...)用于处理所有的类型的异常
    {
        cout<<"Divide by zero..."<<endl;
    }

    cout<<"int main() end"<<endl;

    return 0;
}
