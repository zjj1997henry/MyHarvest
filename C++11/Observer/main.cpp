#include <iostream>
#include "Observer.h"
using namespace std;

struct A{
    void A_Print(int a, double b){
        cout<<__FUNCTION__<<endl;
        cout<<a<<","<<b<<endl;
        cout<<endl;    }
};

void M_Print(int a, double b){
    cout<<__FUNCTION__<<endl;
    cout<<a<<","<<b<<endl;
    cout<<endl;
}

int main()
{

    auto lamda_fuc = [&](int a, double b)->void{
        cout<<__FUNCTION__<<endl;
        cout<<a<<","<<b<<endl;
        cout<<endl;
    };

    A a;

    Events<function<void(int ,double)>> event;

    event.Connect(lamda_fuc);
    event.Connect(M_Print);
    event.Connect(bind(&A::A_Print, &a,placeholders::_1,placeholders::_2));

    event.nofify(3,7.0);

    return 0;
}
