#include "Thread.h"
void *ThreadFunc(void* arg)
{
    Task *ptr = (Task*)arg;

    while(true)
    {
        ptr->m_SemLock.Wait();
        ptr->m_Lock.Lock();
        if(ptr->m_bWantStopThread || ptr->m_bIsThreadRunning==false)
        {
            ptr->m_Lock.UnLock();
            pthread_exit(NULL);
        }
        ptr->m_FuncPtr(ptr->m_Arg);
        ptr->m_bIsThdStarted = false;
        ptr->m_Lock.UnLock();
        ptr->m_pParent->Notify(ptr);
    }
}
Task::~Task()
{
    Stop();

}
bool Task::Create()
{
    ScopedLock sc(&m_Lock);
    if(m_Thread !=-1)
    {
        LOGE("Thread is already created");
        return false;
    }
    m_bIsThreadRunning =true;
    if(pthread_create(&m_Thread,NULL,ThreadFunc,this)!=0)
    {
        m_bIsThreadRunning=false;
        LOGE("Failed to create thread");
        return false;
    }
    return true;
}
bool Task::Start(fptr f_ptr, void*arg)
{
    ScopedLock sc(&m_Lock);
    if(m_bIsThreadRunning==false)
    {
        LOGE("thrad is not running state");
        return false;
    }
    if(m_Thread==-1)
    {
        LOGE("Thread is not creatd yet.Please call create() funcy");
        return false;
    }
    m_FuncPtr = f_ptr;
    m_Arg = arg;

    //send the signal
    return m_SemLock.Signal();

}
bool Task::Stop()
{
    ScopedLock sc(&m_Lock);
    if(m_bIsThreadRunning==false)
    {
        LOGE("Thread is Already stopped ");
        return false;
    }
    if(m_bIsThdStarted==false)
    {

        LOGE("Thread is Already stopped ");
        return false;
    }
    m_bIsThreadRunning=false;
    m_bIsThdStarted =false;
    m_bWantStopThread = true;
    pthread_join(m_Thread,NULL);
    return true;
}
