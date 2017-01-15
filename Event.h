#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include "Lock.h"

class Event
{
private:
    Mutex   m_EventLock;
    pthread_cond_t    m_EventCond;
public:
    bool EventSignal();
    bool EventWait();
    bool EventBroadCast();
};


#endif // EVENT_H_INCLUDED
