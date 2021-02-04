#ifndef GTREENODE_H
#define GTREENODE_H

#include "Tree.h"
#include "LinkList.h"
#include "Object.h"


namespace MyLib
{
    template <typename T>
    class GTreeNode:public TreeNode<T>
    {
    public:
        LinkList<GTreeNode<T>*>child;//child成员为单链表

        static GTreeNode<T>* NewNode()
        {
            GTreeNode<T>* ret=new GTreeNode<T>();

            if(ret!=NULL)
            {
                ret->m_flag=true;
            }

            return ret;
        }
    };
}

#endif // GTREENODE_H
