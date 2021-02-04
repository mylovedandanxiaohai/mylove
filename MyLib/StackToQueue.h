        #ifndef STACKTOQUEUE_H
    #define STACKTOQUEUE_H

    #include "LinkStack.h"
    #include "Queue.h"
    //用栈实现队列，用栈的后进先出的特性实现队列的先进先出的特性，用栈实现队列需要使用两个栈
    namespace MyLib
    {
        template <typename T>
        class StackToQueue:public Queue<T>
        {
        protected:
            mutable LinkStack<T>m_stack_in;//入栈
            mutable LinkStack<T>m_stack_out;//出栈
        public:
            void add(const T &e)
            {
                m_stack_in.push(e);
            }

            void remove()
            {
                if(m_stack_out.size()==0)//如果出栈为空，则将入栈的所有元素压入出栈并弹出入栈的元素
                {
                    while(m_stack_in.size()>0)
                    {
                        m_stack_out.push(m_stack_in.top());//在出栈添加入栈的元素
                        m_stack_in.pop();
                    }
                }

                if(m_stack_out.size() > 0)
                  {
                      m_stack_out.pop();
                  }
                  else
                  {
                      THROW_EXCEPTION(InvalidOperationException, "No element...");
                  }
            }

            T front()const//获取队头元素
            {
                if(m_stack_out.size()==0)
                {
                    while(m_stack_in.size()>0)
                    {
                        m_stack_out.push(m_stack_in.top());
                        m_stack_in.pop();
                    }
                }
                if(m_stack_out.size()>0)
                {
                    return m_stack_out.top();
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException,"...");
                }
            }

            void clear()//清除队列
            {
                m_stack_in.clear();
                m_stack_out.clear();
            }

            int length()const//队列长度
            {
                return m_stack_in.size()+m_stack_out.size();
            }
        };
    }

    #endif // STACKTOQUEUE_H
