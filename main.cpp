#include<iostream>
 #include <mutex>

#include <memory>
#include<tuple>
using namespace std;




typedef struct st
{
    int a;
    int b;
}st_t;
void show(int a)
{
    cout<<"show"<<a<<endl;
}
void show1(st_t tb)
{
    cout<<tb.a<<" "<<tb.b<<endl;
}
int show2(int c, char* str)
{
    cout<<c<<"name_str "<<str<<endl;
    return 10;
}


class Rest
{
public:
      struct Base;
        typedef shared_ptr<Base> shared_ptr_type;

        struct Base
        {
            shared_ptr_type m_ptr;
            inline virtual ~Base()=default;
            virtual void Run()=0;
        };

        template<typename Call>
        struct Der:public Base
        {
            Call fun_ptr;
            Der(Call &&ptr):fun_ptr(forward<Call>(ptr))
            {
            }
            void Run()
            {
                fun_ptr();
            }
        };

      template<typename Call,typename...Args>
      Rest(Call && call,Args &&...ar)
      {
            MakeStart(MakeRoutine(bind(forward<Call>(call),forward<Args>(ar)...)));
      }

      void MakeStart(shared_ptr_type b)
        {
            b->m_ptr = b;
          b->Run();
        }
        template<class Call>
        shared_ptr<Der<Call>> MakeRoutine(Call && c)
        {
            return make_shared<Der<Call>>(forward<Call>(c));
        }

};
int main()
{

st_t tb;
tb.a=10;
tb.b=20;

    int i=0;
    Rest(show,1);
   Rest(show1,tb);
    char str[]={'k','r','i'};
   Rest(i=show2,'1',str);
 //a.call();
    //Thread th(func);
    //Thread th1(ret_(2,3));

    return 0;
}
