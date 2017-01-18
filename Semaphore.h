#ifndef SEMAPHORE_H_INCLUDED
#define SEMAPHORE_H_INCLUDED
#include<semaphore.h>


class SemThreadLock
{
private:
      sem_t   m_Sema;
      bool    m_bIsInit;
 public:
        SemThreadLock():m_bIsInit(false)
        {
            sem_init(&m_Sema,0,0);
            m_bIsInit=true;
        }
        ~SemThreadLock();

        bool Wait();
        bool Signal();
};


#endif // SEMAPHORE_H_INCLUDED
