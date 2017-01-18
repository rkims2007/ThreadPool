#ifndef THREADPOOL_H_INCLUDED
#define THREADPOOL_H_INCLUDED

#include "Thread.h"
#include "Lock.h"
#include "Event.h"
#include <vector>
#include <deque>

typedef void*(*fptr)(void*) ;
class Task;
class ThreadPool
{
private:
    typedef struct TaskElement_t
    {
        fptr  m_fptr;
        void*   m_arg;
        TaskElement_t(fptr ptr,void *a)
        {
            m_fptr=ptr;
            m_arg=a;
        }
    }TaskElement;
    int           m_MaxPool;


    vector<Task*>  m_Task;
    deque<TaskElement*>  m_TaskQ;
 public:
        bool InitializePool(const int poolLimit);
        ThreadPool();
        ~ThreadPool();
        bool AddTask(fptr ptr,void*arg);
        void Notify();

};


#endif // THREADPOOL_H_INCLUDED
