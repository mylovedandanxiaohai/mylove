#include <iostream>

using namespace std;

struct Node
{
   int data;
   Node *next;
};

Node* reverse(Node* list)
{
    Node* ret=NULL;

    if((list->next==NULL)||(list==NULL))
    {
        return list;
    }
    else
    {
        Node* guard=list->next;
        ret=reverse(list->next);
        guard->next=list;
        list->next=NULL;
    }

    return ret;
}

Node* creat(int v,int len)
{
    Node* ret=NULL;
    Node* slider=NULL;

    for(int i=0;i<len;i++)
    {
        Node* n=new Node();

        n->data=v++;
        n->next=NULL;

        if(slider==NULL)
        {
            slider=n;
            ret=n;
        }
        else
        {
            slider->next=n;
            slider=n;
        }
    }
    return ret;
}

void print(Node* list)
{
    while(list)
    {
        cout<<list->data<<"->";
        list=list->next;
    }
    cout<<"NULL"<<endl;
}

int sum(unsigned int a)
{
    int ret;

    if(a==1)
    {
        ret=1;
    }
    if(a>1)
    {
        ret=a+sum(a-1);
    }

    return ret;
}

int fun(unsigned int n)
{
    int ret;

    if(n==1)
    {
        ret=1;
    }
    if(n==2)
    {
        ret=2;
    }
    if(n==3)
    {
        ret=4;
    }
    if(n>3)
    {
        ret=fun(n-1)+fun(n-2)+fun(n-3);
    }
    return ret;
}

int fac(unsigned int m)
{
    int ret;

    if(m==1)
    {
        ret=1;
    }
    if(m==2)

    {
        ret=1;
    }
    if(m>2)
    {
        ret=fac(m-1)+fac(m-2);
    }
    return ret;
}

int main()
{
    cout <<fun(15)<< endl;
    cout<<fac(5)<<endl;
    cout<<sum(100)<<endl;

    Node* list=creat(2,5);
    print(list);
    list=reverse(list);
    print(list);

    return 0;
}

