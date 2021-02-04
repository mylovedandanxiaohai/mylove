#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

using namespace std;

namespace MyLib
{
    enum BTTraversal
    {
        PreOrder,
        InOrder,
        PosOrder,
    };

    enum BTNodePos//枚举三种位置
    {
        ANY,
        LEFT,
        RIGHT,
    };

    template <typename T>
    class BTree :public Tree<T>
    {
    protected:
        LinkQueue<BTreeNode<T>*> Queue;

        //基于数据元素的查找
        virtual BTreeNode<T>* find(BTreeNode<T>* node,const T& value)const
        {
            BTreeNode<T>* ret=NULL;//堆空间申请空间

            if(node!=NULL)//当结点部位空时
            {
                if(node->value==value)
                {
                    ret=node;
                }
                else
                {
                    if(ret==NULL)
                    {//递归的方式实现遍历
                        ret=find(node->left,value);
                    }

                    if(ret==NULL)
                    {
                        ret=find(node->right,value);
                    }
                }
            }
            return ret;
        }
        //基于结点的查找
        virtual BTreeNode<T>* find(BTreeNode<T>* node,BTreeNode<T>* obj)const
        {
            BTreeNode<T>* ret=NULL;

            if(node!=NULL)
            {
                if(node==obj)
                {
                    ret=node;
                }
                else
                {
                    if(ret==NULL)
                    {//遍历的实现
                        ret=find(node->left,obj);
                    }
                    if(ret==NULL)
                    {
                        ret=find(node->right,obj);
                    }
                }
            }
            return ret;
        }
        //插入的功能函数的实现
        virtual bool insert(BTreeNode<T>* n,BTreeNode<T>* np,BTNodePos pos)
        {
            bool ret=true;

            if(pos==ANY)
            {
                if(np->left==NULL)
                {
                    np->left=n;
                }
                else if(np->right==NULL)
                {
                    np->right=n;
                }
                else
                {
                    ret=false;
                }
            }
            else if(pos==LEFT)
            {
                if(np->left==NULL)
                {
                    np->left=n;
                }
                else
                {
                   ret=false;
                }
            }
            else if(pos==RIGHT)
            {
                if(np->right==NULL)
                {
                    np->right=n;
                }
                else
                {
                    ret=false;
                }
            }
            else
            {
                ret=false;
            }

            return ret;
        }
        
        virtual void remove(BTreeNode<T>* node,BTree<T>*& ret)
        {
            ret=new BTree<T>();
            {
                if(ret==NULL)
                {
                    THROW_EXCEPTION(NoEoughMemoryException,"...");
                }
                else
                {
                    if(node==root())//当node等于根结点时
                    {
                        this->m_root=NULL;//将根结点清空
                    }
                    else
                    {
                        BTreeNode<T>* parent=dynamic_cast<BTreeNode<T>*>(node->parent);//在堆空间申请一个指向node结点父节点的指针parent
                        if(parent->left==node)//当parent指针的左子树和node相等时
                        {
                            parent->left=NULL;//将左子树清空
                        }
                        else if(parent->right==node)
                        {
                            parent->right=NULL;
                        }
                        node->parent=NULL;
                    }
                    ret->m_root=node;
                }
            }
        }

        virtual void free(BTreeNode<T>* node)
        {
            if(node!=NULL)
            {
                free(node->left);
                free(node->right);
            }
            if(node->flag())
            {
                delete node;
            }
        }

        int count(BTreeNode<T>* node)const
        {
            int  ret=0;

            if(node==NULL)
            {
                ret=0;
            }
            else
            {
                ret=count(node->left)+count(node->right)+1;//递归得方式求左结点与右结点得和+1
            }

            return ret;
        }

        int height(BTreeNode<T>* node)const
        {
            int ret=0;
            int lf;
            int rt;

            if(node==NULL)
            {
                return 0;
            }
            else
            {
                //递归得方式求左右子树得高度  将其进行比较
                lf=height(node->left);
                rt=height(node->right);

                if(lf<rt)
                {
                    ret=rt+1;
                }
                else
                {
                    ret=lf+1;
                }
            }

            return ret;
        }

        int degree(BTreeNode<T>* node) const
        {
            int ret=0;

            if(node==NULL)
            {
                return 0;
            }
            else
            {
                int dl=degree(node->left);
                int dr=degree(node->right);

                ret=(!!node->left+!!node->right);

                if(ret<dl)
                {
                    ret=dl;
                }
                if(ret<dr)
                {
                    ret=dr;
                }
            }

            return ret;
        }

        //二叉树的三种遍历方式,与队列相结合  递归的方式
        void preOrderTraversal(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& QUEUE)
        {
            if(node!=NULL)
            {//先序遍历 先访问根结点 优先对左子树进行遍历  再对右子树进行遍历
                QUEUE.add(node);
                preOrderTraversal(node->left,QUEUE);
                preOrderTraversal(node->right,QUEUE);
            }
        }

        void inOrderTraversal(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& QUEUE)
        {
            if(node!=NULL)
            {//中序遍历  优先对左子树进行遍历 在访问根结点  再访问右结点
                inOrderTraversal(node->left,QUEUE);
                QUEUE.add(node);
                inOrderTraversal(node->right,QUEUE);
            }
        }

        void posOrderTraversal(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& QUEUE)
        {
            if(node!=NULL)
            {//后序遍历  优先访问左子树 再右子树 最后对根结点进行访问
                posOrderTraversal(node->left,QUEUE);
                posOrderTraversal(node->right,QUEUE);
                QUEUE.add(node);
            }
        }
        //克隆功能函数的实现
        //拷贝node为根结点的二叉树(数据元素在对应位置相等)
        BTreeNode<T>* clone(BTreeNode<T>* node)const//clone的是个指针对象
        {
            BTreeNode<T>* ret=NULL;
            if(node!=NULL)
            {
                ret=BTreeNode<T>::NewNode();
                if(ret!=NULL)
                {
                    //用递归实现对左右子树进行拷贝
                    ret->value=node->value;
                    ret->left=clone(node->left);
                    ret->right=clone(node->right);

                    if(ret->left!=NULL)
                    {//如果左子树不为空 设置左子树的父节点
                        ret->left->parent=ret;
                    }
                    if(ret->right!=NULL)
                    {
                        ret->right->parent=ret;
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEoughMemoryException,"...");
                }
            }

            return ret;
        }
        //两棵二叉树的相加实现
        BTreeNode<T>* add(BTreeNode<T>* L,BTreeNode<T>* R)const
        {
            BTreeNode<T>* ret=NULL;

            if((L==NULL)&&(R!=NULL))//当左子树为空 右子树不为空时
            {
                ret=clone(R);//直接对右子树进行clone
            }
            else if((L!=NULL)&&(R==NULL))
            {
                ret=clone(L);
            }

            else if((L!=NULL)&&(R!=NULL))
            {
                ret=BTreeNode<T>::NewNode();

                if(ret!=NULL)
                {//当申请的ret不为空时 将左右子树的结点进行相加
                    ret->value=L->value+R->value;
                    ret->left=add(L->left,R->left);
                    ret->right=add(L->right,R->right);

                    if(ret->left!=NULL)
                    {//设置左子树的父亲
                        ret->left->parent=ret;
                    }
                    if(ret->right!=NULL)
                    {//设置右子树的父亲
                        ret->right->parent=ret;
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEoughMemoryException,"...");
                }
            }

            return ret;
        }

        void traversal(BTTraversal order,LinkQueue<BTreeNode<T>*>& QUEUE)
        {
            switch (order)
            {
            case PreOrder:
                preOrderTraversal(root(),QUEUE);
                break;

            case InOrder:
                inOrderTraversal(root(),QUEUE);
                break;

            case PosOrder:
                posOrderTraversal(root(),QUEUE);
                break;

            default:
                THROW_EXCEPTION(InvalidParameterException,"...");
                break;
            }
        }
        public:
        //插入结点
        bool insert(TreeNode<T>* node)
        {           
            return insert(dynamic_cast<BTreeNode<T>*>(node),ANY);
        }
        //插入结点,没有位置的要求
        virtual bool insert(TreeNode<T>* node,BTNodePos pos)
        {
            bool ret=true;

            if(node!=NULL)
            {
                if(this->m_root==NULL)
                {
                    node->parent=NULL;
                    this->m_root=node;
                }
                else
                {
                    BTreeNode<T>* np=find(node->parent);//此处的查找需要在左右子树进行查找操作

                    if(np!=NULL)
                    {
                        ret=insert(dynamic_cast<BTreeNode<T>*>(node),np,pos);
                    }
                    else
                    {
                        //THROW_EXCEPTION(InvalidParameterException,"...");
                        cout<<"error"<<endl;
                    }
                }
            }
            else
            {
                //THROW_EXCEPTION(InvalidParameterException,"...");
                cout<<"other error"<<endl;
            }

            return ret;
        }

        bool insert(const T& value, TreeNode<T>* parent)
        {
            return insert(value,parent,ANY);
        }

        virtual bool insert(const T& value, TreeNode<T>* parent,BTNodePos pos)
        {
            bool ret=true;

            BTreeNode<T>* node=BTreeNode<T>::NewNode();

            if(node==NULL)
            {
                THROW_EXCEPTION(NoEoughMemoryException,"...");
            }
            else
            {
                node->value=value;
                node->parent=parent;

                ret=insert(node,pos);

                if(!ret)
                {
                    delete node;
                }
            }

            return ret;
        }
        //删除得是整棵子树
        //基于值得删除
        SharedPointer< Tree<T> > remove(const T& value)
        {
            BTree<T>* ret=NULL;
            BTreeNode<T>* node=find(value);//在BTreeNode中申请一个指向找到value值得指针node
            if(node==NULL)
            {
                THROW_EXCEPTION(InvalidParameterException,"...");
            }
            else
            {
                remove(node,ret);
                //cout<<node->parent<<endl;
                Queue.clear();
            }
            return ret;
        }
        //基于结点的删除
        SharedPointer< Tree<T> > remove(TreeNode<T>* node)
        {
            BTree<T>* ret=NULL;
            node=find(node);//将node结点找到

            if(node!=NULL)//当其不为空时 进行删除
            {
                remove(dynamic_cast<BTreeNode<T>*>(node),ret);

                Queue.clear();
            }
            else//否则抛出异常
            {
                THROW_EXCEPTION(InvalidParameterException,"...");
            }
            return ret;
        }
        
        //查找结点
        BTreeNode<T>* find(const T& value)const
        {
            return find(root(),value);
        }

        BTreeNode<T>* find(TreeNode<T>* node)const
        {
            return find(root(), dynamic_cast<BTreeNode<T>*>(node));//将指向父类TreeNode的指针node强制转换指向子类对象BTreeNode
        }

        //根结点访问函数
        BTreeNode<T>* root()const
        {
            return dynamic_cast<BTreeNode<T>*>(this->m_root);
        }
        //树的度访问函数
        int degree()const
        {
            return degree(root());
        }
        //树的高度访问函数
        int height()const
        {
            return height(root());
        }
        //树的结点数目访问函数
        int count()const
        {
             return count(root());
        }
        //清空树
        void clear()
        {
            free(root());

            this->m_root=NULL;
        }

        bool begin()
        {
            bool ret=(root()!=NULL);

            if(ret)
            {
                Queue.clear();//清空队列
                Queue.add(root());//将根结点加入队列
            }
            return ret;
        }

        bool end()
        {
            return (Queue.length()==0);
        }

        bool next()
        {
            bool ret=(Queue.length()>0);
            {
                BTreeNode<T>* node=Queue.front();
                Queue.remove();//队头元素出队列 == 根结点
                //将队头元素的子节点入队
                if(node->left!=NULL)
                {
                    Queue.add(node->left);
                }
                if(node->right!=NULL)
                {
                    Queue.add(node->right);
                }

            return ret;
            }
        }

        T current()
        {
            if(!end())
            {
                return Queue.front()->value;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        SharedPointer<Array<T>>traversal(BTTraversal order)
        {
            DynamicArray<T>* ret=NULL;
            LinkQueue<BTreeNode<T>*> QUEUE;

            traversal(order,QUEUE);

            ret=new DynamicArray <T>(QUEUE.length());//将队列应用

            if(ret!=NULL)
            {
                for(int i=0;i<ret->length();i++,QUEUE.remove())
                {
                    ret->set(i,QUEUE.front()->value);
                }
            }
            else
            {
                THROW_EXCEPTION(NoEoughMemoryException,"...");
            }

            return ret;
        }
        //克隆的实现
        SharedPointer< BTree<T>>clone()const
        {
            BTree<T>* ret=new BTree<T>();

            if(ret!=NULL)
            {
                ret->m_root=clone(root());
            }
            else
            {
                THROW_EXCEPTION(NoEoughMemoryException,"...");
            }

            return ret;
        }

        SharedPointer<BTree<T>>add(const BTree<T>& other)const
        {
            BTree<T>* ret=new BTree<T>();

            if(ret!=NULL)
            {
                ret->m_root=add(root(),other.root());
            }
            else
            {
                THROW_EXCEPTION(NoEoughMemoryException,"...");
            }

            return ret;
        }

        ~BTree()
        {
            clear();
        }
    };
}

#endif // BTREE_H
