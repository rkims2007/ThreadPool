#ifndef THREADPOOL_H_INCLUDED
#define THREADPOOL_H_INCLUDED

#include "Thread.h"
#include "Mutex.h"
#include "Event.h"


class ThreadPool
{
private:
    const int m_MaxPool;
    Functor   m_FuncPtr;
    void*     m_Arg;
};


#endif // THREADPOOL_H_INCLUDED
