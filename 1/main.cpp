#include <iostream>

using namespace std;

long sum(int v)
{
    long ret=0;

    if(v>0)
    {
        ret=(v+1)*v/2;
    }

    return ret;
}

int main()
{
    cout << "sum(100)=" <<sum(100)<< endl;
    return 0;
}
