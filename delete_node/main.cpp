//二叉树的经典面试题目
#include <iostream>

using namespace std;

template <typename T>
struct BTreeNode
{
    BTreeNode* left;
    BTreeNode* right;
    BTreeNode* parent;
    int value;
};

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
                BTreeNode<T>*& parent_child=(parent->left==node)?parent->left:parent->right;

                //parent=node->parent;
                parent_child=node_child;
                node_child->parent=parent;//删除结点的操作
            }
            else
            {
                node_child->parent=NULL;
            }
            /*if(node->flag())
            {
                delete node;
            }*/
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

int main()
{

    BTreeNode<int>* ns=creatTree<int>();

    printInOrder(ns);

    cout<<endl;

    ns=delOdd(ns);

    printInOrder(ns);

    return 0;
}
