#ifndef LOCK_INCLUDED
#define LOCK_INCLUDED

#include<pthread>

class Mutex
{
private:
    pthraed_mutex_t  m_Mutex;
    bool             m_bIsLocked;
public:
    Mutex();
    bool Lock();
    bool UnLock();
    bool IsLocked();

};

#endif // LOCK_INCLUDED
