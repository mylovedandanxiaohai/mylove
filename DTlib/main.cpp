#include <iostream>
#include "BTreeNode.h"

using namespace std;
using namespace DTLib;

int main()
{
    try
    {
        throw ArithmeticException("test",__FILE__,__LINE__);
    }
    catch(const Exception& e)
    {
        cout<<" catch(const Exception&e)"<<endl;
        cout<<e.message()<<endl;
        cout<<e.location()<<endl;
    }

    catch(const ArithmeticException& e)
    {
        cout<<" catch(const ArithmeticException&e)"<<endl;
        cout<<e.message()<<endl;
        cout<<e.location()<<endl;
    }


    return 0;
}
