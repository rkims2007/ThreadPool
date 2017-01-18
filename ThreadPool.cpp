#include "ThreadPool.h"

ThreadPool::ThreadPool()
{

}
ThreadPool::~ThreadPool()
{
    for(int i=0;i<m_Task.size();i++)
    {
        Task *ptr = m_Task[i];
        delete ptr;
    }
}

bool ThreadPool::InitializePool(const int poollimit)
{
    m_MaxPool = poollimit;
    return true;
}
bool ThreadPool::AddTask(fptr ptr,void *arg)
{
    int TaskSize = m_Task.size();
    if(TaskSize <m_MaxPool)
    {
        Task *t=new Task(this);
        if(t->Create()==false)
        {
            return false;
        }
        t->Start(ptr,arg);
        m_Task.push_back(t);
        return true;
    }
    TaskElement *ta=new TaskElement(ptr,arg);
    m_TaskQ.push_back(ta);

   return true;
}
void ThreadPool::Notify()
{
    if(m_TaskQ.empty())
    {
        return;
    }
    TaskElement *ptr = m_TaskQ.front();
    m_TaskQ.pop_front();
    for(int i=0;i<m_Task.size();i++)
    {
        Task *tr = m_Task[i];
        if(tr->IsRunnning()==false)
        {
            tr->Start(ptr->m_fptr,ptr->m_arg);
        }
    }

}
