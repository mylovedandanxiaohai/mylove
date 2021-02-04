#ifndef GTREE_H
#define GTREE_H

#include "TreeNode.h"
#include "GTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace MyLib
{
    template <typename T>
    class GTree:public Tree<T>
    {
    protected:
        LinkQueue <GTreeNode<T>*> m_queue;


        //基于数据元素值的查找，都是遍历实现的
        GTreeNode<T>* find(GTreeNode<T>* node, const T& value)const
            {
              GTreeNode<T>* ret = NULL;
              if(node != NULL)
              {
                  //如果根结点的就是目标结点
                  if(node->value == value)
                  {
                       return node;
                  }
                  else
                  {
                      //遍历根节点的子结点
                      for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                      {
                          //对每个子子结点进行查找
                          ret = find(node->child.current(), value);
                      }
                  }
              }
              return ret;
            }
        //基于结点得查找
        GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj)const
           {
             GTreeNode<T>* ret = NULL;
             //根结点为目标结点
             if(node == obj)
             {
                 return node;
             }
             else
             {
                 if(node != NULL)
                 {
                     //遍历子结点
                     for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                     {
                         ret = find(node->child.current(), obj);
                     }
                 }
             }
             return ret;
           }


        void free(GTreeNode<T>* node)
        {
            if(node!=NULL)
            {
                for(node->child.move(0); !node->child.end(); node->child.next())
                {
                    free(node->child.current());
                }

                if(node->flag())
                {
                    delete node;
                }
            }
        }

        /*
         * 删除操作成员函数的设计要点
         *   将被删除结点所代表的子树进行删除
         *   删除函数返回一颗堆空间中的树
         *   具体返回值为指向树的智能指针对象
         */
        void remove(GTreeNode<T>* node,GTree<T>*& ret)
        {
            ret=new GTree<T>();

            if(ret==NULL)
            {
                THROW_EXCEPTION(NoEoughMemoryException,"...");
            }
            else
            {
                if(root()!=node)
                {
                    //获取删除结点的父结点的子结点链表
                    LinkList<GTreeNode<T>*>& child=dynamic_cast<GTreeNode<T>*>(node->parent)->child;
                    child.remove(child.find(node)); //从链表中删除结点
                    node->parent=NULL;//结点的父结点置NULL
                }
                else
                {
                    this->m_root=NULL;
                }
            }
        }

        int count(GTreeNode<T>* node)const
        {
            int ret=0;
            if(node!=NULL)
            {
                ret=1;
                //遍历根结点的子节点
                for(node->child.move(0);!node->child.end();node->child.next())
                {
                    ret+=count(node->child.current());//对结点进行统计
                }
            }

            return ret;
        }

        int degree(GTreeNode<T>* node)const
        {
            int ret=0;
            if(node!=NULL)
            {
               ret=node->child.length();

               for(node->child.move(0);!node->child.end();node->child.next())
               {
                   int d=degree(node->child.current());

                   if(ret<d)
                   {
                       ret=d;
                   }
               }
            }

            return ret;
        }

        int height(GTreeNode<T>* node)const
        {
            int ret=0;

            if(node!=NULL)
            {
                for(node->child.move(0);!node->child.end();node->child.next())
                {
                    int h=height(node->child.current());

                    if(ret<h)
                    {
                        ret=h;
                    }
                }

                ret=ret+1;
            }

            return ret;
        }
    public:
        //插入结点
        //以结点的方式插入
        bool insert(TreeNode<T>* node)
        {
            bool ret=true;

            if(node!=NULL)//当结点不为空时
            {
                if(this->m_root==NULL)//如果此时的根结点为空
                {
                    node->parent=NULL;//node结点就是根结点
                    this->m_root=node;
                }
                else
                {
                    GTreeNode<T>* np=find(node->parent);//在堆空间创建np指向node的父节点
                    if(np!=NULL)
                    {
                        GTreeNode<T>* n=dynamic_cast<GTreeNode<T>*>(node);//noded的类型为TreeNode,需要将其强制转换为GTreeNode

                        if(np->child.find(n)<0)
                        {
                            ret=np->child.insert(n);
                        }
                    }
                    else
                    {
                        THROW_EXCEPTION(InvalidOperationException,"...");
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }

            return ret;
        }

        bool insert(const T& value, TreeNode<T>* parent)
        {
            bool ret=true;

            GTreeNode<T>* node=GTreeNode<T>::NewNode();

            if(node!=NULL)
            {
                node->value=value;
                node->parent=parent;

                insert(node);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }

            return ret;
        }

        //删除结点
        SharedPointer< Tree<T> > remove(const T& value)
        {
            GTree<T>* ret=NULL;

            GTreeNode<T>* node=find(value);

            if(node!=NULL)
            {
                remove(node,ret);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }

            return ret;
        }

        SharedPointer< Tree<T> > remove(TreeNode<T>* node)
        {
            GTree<T>* ret=NULL;
            node=find(node);

            if(node!=NULL)
            {
                remove(dynamic_cast<GTreeNode<T>*>(node),ret);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }

            return NULL;
        }

        //查找结点
        GTreeNode<T>* find(const T& value)const
        {
            return find(root(),value);
        }

        GTreeNode<T>* find(TreeNode<T>* node)const
        {
            return find(root(),dynamic_cast<GTreeNode<T>*>(node));//强制类型转换将TreeNode类型转换为GTreeNode类型
        }//root对应的root的类型也应该一样

        //根结点访问函数
        GTreeNode<T>* root()const
        {
            return dynamic_cast<GTreeNode<T>*>(this->m_root);
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
        //树中结点的遍历
        //树是一种非线性的数据结构，遍历树中结点可以采用游标的方式。
        //A、在树中定义一个游标（GTreeNode<T>* node）
        //B、遍历开始前将游标指向根结点
        //C、获取游标指向的数据元素
        //D、通过结点中的child成员移动游标

        bool begin()
        {
            bool ret=(root()!=NULL);

            if(ret)
            {
                m_queue.clear();//清空队列
                m_queue.add(root());//将根结点加入队列
            }
            return ret;
        }

        bool end()
        {
            return (m_queue.length()==0);
        }

        bool next()
        {
            bool ret=(m_queue.length()>0);
            {
                GTreeNode<T>* node=m_queue.front();
                m_queue.remove();//队头元素出队列
                //将队头元素的子节点入队
                for(node->child.move(0);!node->child.end();node->child.next())
                {
                    m_queue.add(node->child.current());
                }

            return ret;
            }
        }

        T current()
        {
            if(!end())
            {
                return m_queue.front()->value;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"...");
            }
        }

        ~GTree()
        {
            clear();
        }
    };
}

#endif // GTREE_H
