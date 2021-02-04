#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace MyLib
{
    template <int N,typename V,typename E>
    class MatrixGraph :public Graph <V,E>
    {
    protected:
        V* m_vertexes[N];
        E* m_edges[N][N];
        int m_eCount;
    public:
        MatrixGraph()//构造函数
        {
            for(int i=0;i<vCount();i++)//遍历的实现
            {
                m_vertexes[i]=NULL;

                for(int j=0;j<vCount();j++)
                {
                    m_edges[i][j]=NULL;
                }
            }
            m_eCount=0;
        }

        V getVertex(int i)
        {
            V ret;

            if(!getVertex(i,ret))
            {
                THROW_EXCEPTION(InvalidParameterException,"...");
            }

            return ret;
        }
        //顶点的获取
        bool getVertex(int i,V& value)
        {
            int ret=((0<=i)&&(i<vCount()));

            if(ret)
            {
                if(m_vertexes[i]!=NULL)
                {
                    value=*(m_vertexes[i]);//将值赋给value
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException,"0.0");
                }
            }

            return ret;
        }
        //顶点的设立
        bool setVertex(int i,const V& value)
        {
            bool ret=((0<=i)&&(i<vCount()));

            if(ret)
            {
                V* data=m_vertexes[i];

                if(data==NULL)
                {
                    data=new V();
                }
                if(data!=NULL)
                {
                    *data=value;

                    m_vertexes[i]=data;
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException,"0.0");
                }
            }

            return ret;
        }

        SharedPointer<Array<int>>getAdjacent(int i)
        {
            DynamicArray<int>* ret=NULL;

            if((0<=i)&&(i<vCount()))
            {
                int n=0;

                for(int j=0;j<vCount();j++)
                {
                    if(m_edges[i][j]!=NULL)
                    {
                        n++;
                    }
                }

                ret=new DynamicArray<int>(n);

                if(ret!=NULL)
                {
                    for(int j=0,k=0;j<vCount();j++)
                    {
                        if(m_edges[i][j]!=NULL)
                        {
                            ret->set(k++,j);
                        }
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEoughMemoryException,"0.0");
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"0.0");
            }

            return ret;
        }
        //获取边
        E getEdge(int i,int j)
        {
            E ret;

            if(!getEdge(i,j,ret))
            {
                THROW_EXCEPTION(InvalidParameterException,"0.0");
            }

            return ret;
        }
        //两条边以及值得获取
        bool getEdge(int i, int j, E& value)
        {
            bool ret=((0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount()));

            if(ret)
            {
                if(m_edges[i][j]!=NULL)
                {
                    value=*(m_edges[i][j]);
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException,"...");
                }
            }

            return ret;
        }
        //对两条边得设置  以及边得权值得设置
        bool setEdge(int i, int j,const E& value)
        {
            bool ret=((0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount()));

            if(ret)
            {
                E* ne=m_edges[i][j];

                if(ne==NULL)
                {
                    ne=new E();

                    if(ne!=NULL)
                    {
                        *ne=value;

                        m_edges[i][j]=ne;

                        m_eCount++;
                    }
                    else
                    {
                        THROW_EXCEPTION(NoEoughMemoryException,"...");
                    }
                }
                else
                {
                    *ne=value;
                }
            }

            return ret;
        }
        //边的删除
        bool removeEdge(int i,int j)
        {
             bool ret=((0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount()));

             if(ret)
             {
                 E* toDel=m_edges[i][j];

                 m_edges[i][j]=NULL;

                 if(toDel!=NULL)
                 {
                     m_eCount--;

                     delete toDel;
                 }
             }

             return ret;
        }

        int vCount()//图的数量总和
        {
            return N;
        }

        int eCount()
        {
            return m_eCount;
        }
        //入度与出度的计算方法是 对指向该结点的和该结点指出的综合的计算
        //出度
        int OD(int i)
        {
            int ret=0;

            if((0<=i)&&(i<vCount()))
            {
                for(int j=0;j<vCount();j++)
                {
                    if(m_edges[i][j]!=NULL)
                    {
                        ret++;
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"...");
            }

            return ret;
        }
        //入度
        int ID(int i)
        {
            int ret=0;

            if((0<=i)&&(i<vCount()))
            {
                for(int j=0;j<vCount();j++)
                {
                    if(m_edges[j][i]!=NULL)
                    {
                        ret++;
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"...");
            }

            return ret;
        }
        //析构函数
        ~MatrixGraph()
        {
            for(int i=0;i<vCount();i++)
            {
                for(int j=0;j<vCount();j++)
                {
                    delete m_edges[i][j];
                }
                delete m_vertexes[i];
            }
        }
    };
}

#endif // MATRIXGRAPH_H
