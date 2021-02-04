#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace MyLib
{
    template <typename T>
    class TreeNode:public Object
    {
    protected:
        bool m_flag;

        TreeNode(const TreeNode<T>&);
        TreeNode<T>& operator = (const TreeNode<T>&);

        void* operator new(unsigned int size)throw()
        {
            return Object::operator new(size);
        }
    public:
        T value;//存储数据元素
        TreeNode<T>* parent;
        TreeNode()
        {
            m_flag=false;
            parent=NULL;
        }

        bool flag()const
        {
            return m_flag;
        }

        virtual ~TreeNode()=0;
    };

    template <typename T>
    TreeNode<T>::~TreeNode()
    {

    }
}

#endif // TREENODE_H
