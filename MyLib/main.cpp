#include <iostream>
#include "ListGraph.h"

using namespace std;
using namespace MyLib;

int main()
{
    ListGraph<char,int>g(4);

    g.setVertex(0,'A');
    g.setVertex(1,'B');
    g.setVertex(2,'C');
    g.setVertex(3,'D');

    for(int i=0;i<g.vCount();i++)
    {
        cout<<i<<":"<<g.getVertex(i)<<endl;
    }


    g.addVertex('E');

    for(int i=0;i<g.vCount();i++)
    {
        cout << i << " : " << g.getVertex(i) << endl;
    }

    g.removeVertex();

    g.setEdge(0,1,5);
    g.setEdge(0,3,5);
    g.setEdge(1,2,8);
    g.setEdge(2,3,2);
    g.setEdge(3,1,9);

    cout << "W(0,1) : " << g.getEdge(0, 1) <<endl;
    cout << "W(0,3) : " << g.getEdge(0, 3) <<endl;
    cout << "W(1,2) : " << g.getEdge(1, 2) <<endl;
    cout << "W(2,3) : " << g.getEdge(2, 3) <<endl;
    cout << "W(3,1) : " << g.getEdge(3, 1) <<endl;



}
/*
template<typename V,typename E>
Graph<V,E>& Graphcomplex()
{
    static ListGraph<V,E>g(5);

    g.setEdge(0,1,10);
    g.setEdge(0,3,30);
    g.setEdge(0,4,100);

    g.setEdge(1,2,50);

    g.setEdge(2,4,40);

    g.setEdge(3,2,20);
    g.setEdge(3,4,60);
}

int main()
{
    Graph<int,int>&g=Graphcomplex<int,int>();
    SharedPointer<Array<int>>p=g.dijktra(0,3,65535);

    for(int i=0;i<p->length();i++)
    {
        cout<<(*p)[i]<<endl;
    }

    cout<<endl;

    return 0;
}



    MatrixGraph<9,char,int>g;
    const char* VD="ABCDEFGHI";

    for(int i=0;i<9;i++)
    {
        //cout<<"Error"<<endl;;
        g.setVertex(0,VD[i]);
    }

    g.setEdge(0,1,0);
    g.setEdge(1,0,0);

    g.setEdge(0,3,0);
    g.setEdge(3,0,0);

    g.setEdge(0,4,0);
    g.setEdge(4,0,0);

    g.setEdge(1,2,0);
    g.setEdge(2,1,0);

    g.setEdge(1,4,0);
    g.setEdge(4,1,0);

    g.setEdge(2,5,0);
    g.setEdge(5,2,0);

    g.setEdge(3,6,0);
    g.setEdge(6,3,0);

    g.setEdge(4,6,0);
    g.setEdge(6,4,0);

    g.setEdge(6,7,0);
    g.setEdge(7,6,0);

    g.setEdge(7,8,0);
    g.setEdge(8,7,0);


    SharedPointer<Array<int>>sa=g.BFS(0);

    for(int i=0;i<sa->length();i++)
    {
        //cout<<"Debug Error";
        cout<<(*sa)[i]<<" ";
    }

    cout<<endl;

    return 0;

    ListGraph<char,int>g;
    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');

    for(int i=0;i<g.vCount();i++)
    {
        cout<<i<<":"<<g.getVertex(i)<<endl;
    }

    cout<<endl;

    g.setEdge(0,1,5);
    g.setEdge(0,3,5);
    g.setEdge(1,2,8);
    g.setEdge(2,3,2);
    g.setEdge(3,1,9);

    cout<<"W(0,1):"<<g.getEdge(0,1)<<endl;
    cout<<"W(0,3):"<<g.getEdge(0,3)<<endl;
    cout<<"W(1,2):"<<g.getEdge(1,2)<<endl;
    cout<<"W(2,3):"<<g.getEdge(2,3)<<endl;
    cout<<"W(3,1):"<<g.getEdge(3,1)<<endl;

 MatrixGraph<3,int,int> l;
    l.setEdge(0,1,1);
    l.setEdge(1,0,2);
    l.setEdge(1,2,3);

    cout<<"l.vCount()= "<<l.vCount()<<endl;
    cout<<"l.eCount()= "<<l.eCount()<<endl;
    cout<<"l.ID(1)= "<<l.ID(1)<<endl;
    cout<<"l.OD(1)= "<<l.OD(1)<<endl;
    cout<<"l.TD(1)= "<<l.TD(1)<<endl;


template <typename T>
BTreeNode<T>* creatTree()
{
    static BTreeNode<int> ns[9];

    for(int i=0;i<9;i++)
    {
        ns[i].value=i;
        ns[i].parent=NULL;
        ns[i].left=NULL;
        ns[i].right=NULL;
    }
    ns[0].left=&ns[1];
    ns[0].right=&ns[2];
    ns[1].parent=&ns[0];
    ns[2].parent=&ns[0];

    ns[1].left=&ns[3];
    ns[1].right=NULL;
    ns[3].parent=&ns[1];

    ns[2].left=&ns[4];
    ns[2].right=&ns[5];
    ns[4].parent=&ns[2];
    ns[5].parent=&ns[2];

    ns[3].left=NULL;
    ns[3].right=&ns[6];
    ns[6].parent=&ns[3];

    ns[4].left=&ns[7];
    ns[4].right=NULL;
    ns[7].parent=&ns[4];

    ns[5].left=&ns[8];
    ns[5].right=NULL;
    ns[8].parent=&ns[5];


    return ns;
}

template <typename T>
void printInOrder(BTreeNode<T>* node)
{
    if(node!=NULL)
    {
        printInOrder(node->left);
        cout<<node->value<<" ";
        printInOrder(node->right);
    }
}

template <typename T>
void printDualList(BTreeNode<T>* node)
{
    BTreeNode<T>* g=node;

    cout<<"head->tail"<<endl;

    while(node!=NULL)
    {
        cout<<node->value<<" ";

        g=node;

        node=node->right;
    }
    cout<<endl;

    cout<<"tail->head"<<endl;

    while(g!=NULL)
    {
        cout<<g->value<<" ";
        g=g->left;
    }
    cout<<endl;
}

template <typename T>//删除单度点的实现
BTreeNode<T>* delOdd(BTreeNode<T>* node)
{
    BTreeNode<T>* ret=NULL;

    if(node!=NULL)
    {//当结点为单度结点是
        if(((node->left!=NULL)&&(node->right==NULL))||((node->left==NULL)&&(node->right!=NULL)))
        {//再堆空间申请一个parent指针指向node的父节点
            BTreeNode<T>* parent=dynamic_cast<BTreeNode<T>*>(node->parent);
            BTreeNode<T>* node_child=(node->left!=NULL)?node->left:node->right;
            //在堆空间申请一个node_child指针 (看其是否指向左结点或者右结点)
            if(parent!=NULL)
            {   //在堆空间申请一个parent_child指针 (看其是否指向左结点或者右结点)
                //有指针引用
                BTreeNode<T>*& parent_child=(parent->left==node)?parent->left:parent->right;

                //parent=node->parent;
                parent_child=node_child;
                node_child->parent=parent;//删除结点的操作
            }
            else
            {
                node_child->parent=NULL;
            }
            if(node->flag())
            {
                delete node;
            }
            ret=delOdd(node_child);//递归的实现
        }
        else
        {//当度为2时的递归实现
            delOdd(node->left);
            delOdd(node->right);

            ret=node;
        }
    }

    return ret;
}

template <typename T>
void delOdd1(BTreeNode<T>*& node)
{
    //BTreeNode<T>* ret=NULL;

    if(node!=NULL)
    {
        if(((node->left!=NULL)&&(node->right==NULL))||((node->left==NULL)&&(node->right!=NULL)))
        {
            BTreeNode<T>* node_child=(node->left!=NULL)?node->left:node->right;

            if(node->flag())
            {
                delete node;
            }
            node=node_child;//引用 别名
            delOdd1(node);
        }
        else
        {
            delOdd1(node->left);
            delOdd1(node->right);
        }
    }
    // ret;
}

template <typename T>
void inOrderThread(BTreeNode<T>* node,BTreeNode<T>*& pre)
{
    if(node!=NULL)
    {
        inOrderThread(node->left,pre);
        node->left=pre;
        if(pre!=NULL)
        {
            pre->right=node;
        }
        pre=node;
        inOrderThread(node->right,pre);
    }
}

template <typename T>
BTreeNode<T>* inOrderThread1(BTreeNode<T>* node)
{
    BTreeNode<T>* pre=NULL;

    inOrderThread(node,pre);

    while((node!=NULL)&&(node->left!=NULL))
    {
        node=node->left;
    }
    return node;
}

int main()
{

    BTreeNode<int>* ns=creatTree<int>();

    printInOrder(ns);

    cout<<endl;

    delOdd1(ns);

    printInOrder(ns);

    cout<<endl;

    ns=inOrderThread1(ns);

    printDualList(ns);

    return 0;
}


    BTree <int> l;
    BTreeNode<int>* n=NULL;

    l.insert(1,NULL);//根结点

    n=l.find(1);
    l.insert(2,n);
    l.insert(3,n);

    n=l.find(2);
    l.insert(4,n);
    l.insert(5,n);

    n=l.find(4);
    l.insert(8,n);
    l.insert(9,n);

    n=l.find(5);
    l.insert(10,n);

    n=l.find(3);
    l.insert(6,n);
    l.insert(7,n);

    BTree<int>l1;
    //BTreeNode<int>* m=NULL;

    l1.insert(0,NULL);//根结点

    n=l1.find(0);
    l1.insert(6,n);
    l1.insert(2,n);

    n=l1.find(2);
    l1.insert(7,n);
    l1.insert(8,n);


    cout<<l.count()<<endl;
    cout<<l.height()<<endl;
    cout<<l.degree()<<endl;

    SharedPointer<BTree<int>>btClone=l.clone();
    SharedPointer<BTree<int>>r=l.add(l1);



    cout<<endl;

    int a[]={8,9,10,13,15};
    //int b;
    int c;
    int d;

    cout<<"old tree:"<<endl;
    for(int i=0;i<5;i++)
    {
        TreeNode<int>* node=l.find(a[i]);

        while(node)
        {
            b=node->value;
            cout<<b<<" ";
            node=node->parent;
        }
        cout<<endl;
    }

    cout<<endl;

    cout<<"clone tree:"<<endl;


    for(int i=0;i<5;i++)
    {
        c=a[i];
        TreeNode<int>* node=btClone->find(c);

        while(node)
        {
            d=node->value;
            cout<<d<<" ";
            node=node->parent;
        }
        cout<<endl;
    }
*/
    /*
    cout<<endl;

    cout<<"The add clone tree:"<<endl;

    for(int i=0;i<5;i++)
    {
        c=a[i];
        TreeNode<int>* node=r->find(c);//每次找到叶节点

        while(node)
        {
            d=node->value;
            cout<<d<<" ";
            node=node->parent;
        }
        cout<<endl;
    }

    return 0;
}

    for(l.begin();!l.end();l.next())
    {
        //cout<<l.current()<<" ";
    }

    SharedPointer<Array<int>>sp=NULL;

    sp=l.traversal(PosOrder);

    int p;

    for(int i=0;i<(*sp).length();i++)
    {
        p=(*sp)[i];
        cout<<p<<" ";
    }

    for(int i=0;i<5;i++)
    {
        TreeNode<int>* node=l.find(a[i]);

        while(node)
        {
            b=node->value;
            cout<<b<<" ";
            node=node->parent;
        }
        cout<<endl;
    }

 通用树的创建
    GTree<char> t;
    GTreeNode<char>* node=NULL;

    t.insert('A',NULL);

    node=t.find('A');
    t.insert('B',node);
    t.insert('C',node);
    t.insert('D',node);

    node=t.find('B');
    t.insert('E',node);
    t.insert('F',node);

    node=t.find('C');
    t.insert('G',node);

    node=t.find('D');
    t.insert('H',node);
    t.insert('I',node);
    t.insert('J',node);

    node=t.find('E');
    t.insert('K',node);
    t.insert('L',node);

    node=t.find('H');
    t.insert('M',node);

    //t.remove('D');

    cout<<t.count()<<endl;
    cout<<t.height()<<endl;
    cout<<t.degree()<<endl;

    for(t.begin();!t.end();t.next())
    {
        cout<<t.current()<<endl;
    }

递归的一些操作  例如:链表的翻转以及相加排序
int sum(unsigned int n)
{
    int ret;

    if(n==1)
    {
        ret=1;
    }
    if(n>1)
    {
        ret=n+sum(n-1);
    }

    return ret;
}

int fac(unsigned int n)
{
    if(n>=3)
    {
        return fac(n-1)+fac(n-2);
    }
    if((n==1)||(n==2))
    {
        return 1;
    }

    return 0;
}
//链表翻转的实现
struct Node
{
    int data;
    Node* next;
};

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

void destroy(Node* list)
{
    while(list)
    {
        Node* del=list;
        list=list->next;
        delete del;
    }
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

Node* reserve(Node* list)//递归的实现
{
    Node* ret=NULL;
    if((list==NULL)||(list->next==NULL))
    {
        ret=list;
    }
    else
    {
        Node* guad=list->next;
        ret=reserve(list->next);
        guad->next=list;
        list->next=NULL;
    }
    return ret;
}



Node* merge(Node* list1, Node* list2)
{
  Node* ret = NULL;
  if(NULL == list1)
  {
    ret = list2;
  }
  else if(NULL == list2)
  {
    ret = list1;
  }
  else if(list1->data < list2->data)
  {
    list1->next = merge(list1->next,list2);
    ret = list1;
  }
  else
  {
    list2->next = merge(list2->next, list1);
    ret = list2;
  }
  return ret;
}

//出不来结果的原因可能是调用get出现问题
//约瑟夫的问题出错的原因可能是current或者remove的问题
    //jusephus(41,1,3);

    DualCircleList <int> l;

    for(int i=0;i<5;i++)
    {
        l.insert(i);
    }

    for(int i=0;i<l.length();i++)
    {
        cout<<l.get(i)<<endl;
    }


//for(l.move(0);!l.end();l.next())//单链表遍历的优化结果
//{
//    cout<<l.current()<<endl;
//}



//约瑟夫环
    DualCircleList<int> l;

    for(int i=0;i<5;i++)
    {
        l.insert(0,i);
        l.set(0,i*i);
        cout<<"i="<<i<<endl;
        cout<<"i*i="<<i*i<<endl;
    }

    return 0;
}

void jusephus(int n, int k, int m)
{
  //构建循环链表
  CircleList<int> cl;
  for(int i = 1; i <= n; i++)
  {
      cl.insert(i);
  }
  //移动当前结点到位置k-1，设置步长为m-1
  cl.move(k-1, m-1);
  while(cl.length() > 0)
  {
      cl.next();//移动到目标位置
      //cout << cl.current() << endl;
      cout<<cl.current()<<endl;
      cout<<1<<endl;
      //删除目标位置结点
      cl.remove(cl.find(cl.current()));
  }
}

void js(int n,int s,int m)
{
    CircleList<int> l;
    for(int i=1;i<=n;i++)
    {
        l.insert(i);
        //cout<<i<<endl;
    }

    l.move(s-1,m-1);

    while(l.length()>0)
    {
        l.next();

        cout<<"l.length()="<<l.length()<<endl;

        cout<<l.current()<<endl;

        l.remove(l.find(l.current()));
    }
}
*/
