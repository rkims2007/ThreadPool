#include"Semaphore.h"

SemThreadLock::~SemThreadLock()
{
    if(m_bIsInit)
    {
        sem_close(&m_Sema);
        sem_destroy(&m_Sema);
    }
}

bool SemThreadLock::Wait()
{
    if(m_bIsInit==false)
    {
        LOGE("Semaphore not init yet");
        return false;
    }
    sem_wait(&m_Sema);
    return true;
}
bool SemThreadLock::Signal()
{
    if(m_bIsInit==false)
    {
        LOGE("Semaphore not init yet");
        return false;
    }
    sem_post(&m_Sema);
    return true;
}
