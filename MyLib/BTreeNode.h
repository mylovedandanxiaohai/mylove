#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace MyLib
{
    template <typename T>
    class BTreeNode: public TreeNode<T>
    {
    public:
        BTreeNode<T>* left;
        BTreeNode<T>* right;

        BTreeNode()//进行初始化
        {
            left=NULL;
            right=NULL;
        }

        //工厂模式
        static BTreeNode<T>* NewNode()
        {
            BTreeNode<T>* ret=new BTreeNode<T>();

            if(ret!=NULL)
            {
                ret->m_flag=true;
            }

            return ret;
        }
    };
}

#endif // BTREENODE_H
