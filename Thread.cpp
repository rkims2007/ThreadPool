#include "Thread.h"
void *ThreadFunc(void* arg)
{
    Task *ptr = (Task*)arg;

    while(true)
    {
        cout<<"thread is in waiting condition"<<pthread_self()<<endl;
        ptr->m_SemLock.Wait();

        ptr->m_Lock.Lock();
        //cout<<"krishna "<<endl;
        if(ptr->m_bWantStopThread || ptr->m_bIsThreadRunning==false)
        {
            ptr->m_Lock.UnLock();
            pthread_exit(NULL);
        }
        while(ptr->m_queue.empty()==false)
        {
            Task::ThreadElement_t   taskelement = ptr->m_queue.front();
            ptr->m_queue.pop_front();
            cout<<ptr<<"in thread excution "<<pthread_self()<<endl;


            taskelement.m_Fptr(taskelement.m_Arg);

        }
        ptr->m_bIsThdStarted=false;
        ptr->m_Lock.UnLock();

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
bool Task::Start(fptr ptr,void*arg)
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
    ThreadElement_t el;
    el.m_Fptr = ptr;
    el.m_Arg = arg;
    if(m_bIsThdStarted==false)
    {
        cout<<"no task is for thread"<<endl;
        m_bIsThdStarted =true;
        m_queue.push_back(el);
        m_SemLock.Signal();
        return true;
    }
    cout<<"queue is running put it into the queue"<<this<<endl;
    m_queue.push_back(el);
    return true;
    //return m_SemLock.Signal();
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
