
#include "ThreadPool.h"
#include<iostream>
// #include <mutex>
//
//#include <memory>
//#include<tuple>
//using namespace std;
//
//
//
//
//typedef struct st
//{
//    int a;
//    int b;
//}st_t;
//void show(int a)
//{
//    cout<<"show"<<a<<endl;
//}
//void show1(st_t tb)
//{
//    cout<<tb.a<<" "<<tb.b<<endl;
//}
//int show2(int c, char* str)
//{
//    cout<<c<<"name_str "<<str<<endl;
//    return 10;
//}
//
//
//class Rest
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
//      Rest(Call && call,Args &&...ar)
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


void *Func(void*arg)
{
    char path[1000] = {0};
    sprintf(path,"./temp/%x",pthread_self());


    FILE* fp = fopen(path,"a+");
    for(int i=0;i<10;i++)
    {
        fprintf(fp,"%d\n",i);
        fflush(fp);
        //cout<<pthread_self()<<"  "<<i<<endl;
    }
}

int main()
{

    ThreadPool *ptr =new ThreadPool();
    ptr->InitializePool(3);
    ptr->AddTask(Func,NULL);
     ptr->AddTask(Func,NULL);
     ptr->AddTask(Func,NULL);
       ptr->AddTask(Func,NULL);
       ptr->AddTask(Func,NULL);
     ptr->AddTask(Func,NULL);
       ptr->AddTask(Func,NULL);
       ptr->AddTask(Func,NULL);
     ptr->AddTask(Func,NULL);
       ptr->AddTask(Func,NULL);
      while(1);
       delete ptr;
       return 0;
 //a.call();
    //Thread th(func);
    //Thread th1(ret_(2,3));

    return 0;
}
