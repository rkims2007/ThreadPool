#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED
#include<iostream>
#include<pthread>
#include "Lock.h"

using namespace std;

//class GenFunctor
//{
//public:
//      struct Base;
//        typedef shared_ptr<Base> shared_ptr_type;
//
//        struct Base
//        {
//            shared_ptr_type m_ptr;
//            inline virtual ~Base()=default;
//            virtual void Run()=0;
//        };
//
//        template<typename Call>
//        struct Der:public Base
//        {
//            Call fun_ptr;
//            Der(Call &&ptr):fun_ptr(forward<Call>(ptr))
//            {
//            }
//            void Run()
//            {
//                fun_ptr();
//            }
//        };
//
//      template<typename Call,typename...Args>
//      GenFunctor(Call && call,Args &&...ar)
//      {
//            MakeStart(MakeRoutine(bind(forward<Call>(call),forward<Args>(ar)...)));
//      }
//
//      void MakeStart(shared_ptr_type b)
//        {
//            b->m_ptr = b;
//          b->Run();
//        }
//        template<class Call>
//        shared_ptr<Der<Call>> MakeRoutine(Call && c)
//        {
//            return make_shared<Der<Call>>(forward<Call>(c));
//        }
//
//};

typedef void*(*fptr)(void*) Funtor;
class Task
{

private:
    Funtor          m_FuncPtr;
    const void*     m_Arg;
    Mutex           m_Lock;
public:


    Task(Funtor pFuncPtr,const void*arg):m_FuncPtr(pFuncPtr),m_Arg(arg),m_Lock(PTHREAD_MUTEX_INITIALIZER)
    {

    }
    bool Start();
    bool Stop();
    bool IsRunnning();
    void Run();


};




#endif // THREAD_H_INCLUDED
