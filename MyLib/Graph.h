#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"

namespace MyLib
{
    template<typename E>
    struct Edge:public Object
    {
        int b;
        int e;
        E data;

        Edge(int i=-1,int j=-1)
        {
            b=i;
            e=j;
        }

        Edge(int i, int j,const E& value)
        {
            b=i;
            e=j;
            data=value;
        }

        bool operator ==(const Edge& obj)
        {
            return (b==obj.b)&&(e==obj.e);
        }

        bool operator !=(const Edge& obj)
        {
            return !(*this==obj);
        }

    };

    template <typename V,typename E>
    class Graph:public Object
    {
    protected:
        template<typename T>
        DynamicArray<T>* toArray (LinkQueue<T>& queue)
        {
            DynamicArray<T>* ret=new DynamicArray<T>(queue.length());

            if(ret)
            {
                for(int i=0;i<ret->length();i++,queue.remove())
                {
                    ret->set(i,queue.front());
                }
            }
            else
            {
                THROW_EXCEPTION(NoEoughMemoryException,"0.0");
            }

            return ret;
        }
    public:
        virtual V getVertex(int x)=0;
        virtual bool getVertex(int x,V& value)=0;
        virtual bool setVertex(int i,const V& value)=0;
        virtual SharedPointer<Array<int>>getAdjacent(int i)=0;
        virtual E getEdge(int i,int j)=0;
        virtual bool getEdge(int i, int j,E& value)=0;
        virtual bool setEdge(int i, int j,const E& value)=0;
        virtual bool removeEdge(int i,int j)=0;
        virtual int vCount()=0;
        virtual int eCount()=0;
        virtual int OD(int i)=0;
        virtual int ID(int i)=0;

        virtual int TD(int i)
        {
            return OD(i)+ID(i);
        }

        SharedPointer<Array<int>>BFS(int i)
        {
            DynamicArray<int>* ret=NULL;

            if((0<=i)&&(i<vCount()))
            {
                LinkQueue<int>q;
                LinkQueue<int>r;
                DynamicArray<bool>visited(vCount());

                for(int i=0;i<visited.length();i++)
                {
                    visited[i]=false;
                }

                q.add(i);

                while(q.length()>0)
                {
                    int v=q.front();

                    q.remove();

                    if(!visited[v])
                    {
                        SharedPointer< Array<int> >aj=getAdjacent(v);

                        for(int j=0;j<aj->length();j++)
                        {
                            q.add((*aj)[j]);
                        }

                        r.add(v);

                        visited[v]=true;
                    }
                }
                ret=toArray(r);
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"0.0");
            }

            return ret;
        }

        SharedPointer<Array<int>>DFS(int i)
        {
            DynamicArray<int>* ret=NULL;

            if((0<=i)&&(i<vCount()))
            {
                LinkStack<int>s;
                LinkQueue<int>r;
                DynamicArray<bool>visited(vCount());

                for(int j=0;j<visited.length();j++)
                {
                    visited[j]=false;
                }

                s.push(i);

                while(s.size()>0)
                {
                    int v=s.top();

                    s.pop();

                    if(!visited[v])
                    {
                        SharedPointer<Array<int>>aj=getAdjacent(v);

                        for(int j=aj->length()-1;j>=0;j--)
                        {
                            s.push((*aj)[j]);
                        }

                        r.add(v);
                        visited[v]=true;
                    }
                }
                ret=toArray(r);
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"...");
            }
            return ret;
        }

        SharedPointer<Array<int>> dijktra(int i,int j,const E&Limit)
        {
            LinkQueue<int> ret;

            if((0<=i)&&(i<vCount())&&(0<=j)&&(j<=vCount()))
            {
                DynamicArray<E>dist(vCount());
                DynamicArray<int>path(vCount());
                DynamicArray<bool>mark(vCount());

                for(int k=0;k<vCount();k++)
                {
                    mark[k]=false;
                    path[k]=-1;

                    //dist[k]=isAdjacent(i,k)?getEdge(i,k):Limit;
                }

                mark[i]=true;

                for(int k=0;k<vCount();k++)
                {
                    E m=Limit;
                    int u=-1;

                    for(int w=0;w<vCount();w++)
                    {
                        if(!mark[w]&&(dist[w]<m))
                        {
                            m=dist[w];
                            u=w;
                        }
                    }

                    if(u==-1)
                    {
                        break;
                    }

                    mark[u]=true;

                    for(int w=0;w<vCount();w++)
                    {
                        //if(!mark[w]&&isAdjacent(u,w)&&(dist[u])+getEdge(u,w)<dist[w])
                        {
                            dist[w]=dist[u]+getEdge(u,w);
                            path[w]=u;
                        }
                    }
                }

                LinkStack<int>s;
                s.push(j);
                for(int k=path[j];k!=-1;k=path[k])
                {
                    s.push(k);
                }

                while(s.size()>0)
                {
                    ret.add(s.top());
                    s.pop();
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"0.0");
            }

            if(ret.length()<2)
            {
                THROW_EXCEPTION(ArithmeticException,"0.0");
            }
        }
    };
}

#endif // GRAPH_H
