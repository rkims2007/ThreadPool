#include "ThreadPool.h"

ThreadPool::ThreadPool()
{

}
ThreadPool::~ThreadPool()
{
    for(int i=0;i<m_TaskQ.size();i++)
    {
        Task *ptr = m_TaskQ[i];
        delete ptr;
    }
}

bool ThreadPool::InitializePool(const int poollimit)
{
    ScopedLock sc(&m_PoolLock);
    m_MaxPool = poollimit;
    for(int i=0; i<m_MaxPool;i++)
    {
        Task *t = new Task();
        cout<<t<<endl;
        t->Create();
        m_TaskQ.push_back(t);
    }
    return true;
}

bool ThreadPool::AddTask(fptr ptr,void *arg)
{
    ScopedLock sc(&m_PoolLock);
    Task *ptr1 = m_TaskQ.front();
    m_TaskQ.pop_front();
     ptr1->Start(ptr,arg);
     m_TaskQ.push_back(ptr1);
   return true;
}
void ThreadPool::Notify(Task *TaskPtr)
{
}
