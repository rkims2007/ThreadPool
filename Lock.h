#ifndef LOCK_INCLUDED
#define LOCK_INCLUDED

#include<pthread.h>
#include "Log.h"

class Mutex
{
private:
    pthread_mutex_t  m_Mutex;

public:
    Mutex():m_Mutex(PTHREAD_MUTEX_INITIALIZER)
    {

    }
    bool Lock()
    {
        if(pthread_mutex_lock(&m_Mutex)!=0)
        {
            LOGE("failed to acquire lock");
            return false;
        }
        return true;
    }
    bool UnLock()
    {
        if(pthread_mutex_unlock(&m_Mutex)!=0)
        {
            LOGE("failed in unlock");
            return false;
        }
        return true;
    }
    ~Mutex()
    {
        pthread_mutex_destroy(&m_Mutex);
    }

};

class ScopedLock
{
private:
     Mutex * m_pScopedLock;
public:
        ScopedLock( Mutex *ptr):m_pScopedLock(ptr)
        {
            if(m_pScopedLock)
            {
                m_pScopedLock ->Lock();
            }
        }
        ~ScopedLock()
        {
            if(m_pScopedLock)
            {
                m_pScopedLock->UnLock();
            }
        }
};

#endif // LOCK_INCLUDED
