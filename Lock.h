0a1,40
> #ifndef LOCK_INCLUDED
> #define LOCK_INCLUDED
> 
> #include<pthread>
> 
> class Mutex
> {
> private:
>     pthraed_mutex_t  m_Mutex;
>     bool             m_bIsLocked;
> public:
>     Mutex();
>     bool Lock();
>     bool UnLock();
>     bool IsLocked();
> 
> };
> 
> class ScopedLock
> {
> private:
>     const Mutex * m_pScopedLock
> public:
>         ScopedLock(const Mutex *ptr):m_pScopedLock(ptr)
>         {
>             if(m_pScopedLock)
>             {
>                 m_pScopedLock ->Lock();
>             }
>         }
>         ~ScopedLock()
>         {
>             if(m_pScopedLock)
>             {
>                 m_pScopedLock->UnLock();
>             }
>         }
> };
> 
> #endif // LOCK_INCLUDED
