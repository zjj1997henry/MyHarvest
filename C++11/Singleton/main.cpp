#include <iostream>
#include "Singletion.h"
#include <string>
using namespace std;

struct A{
    A(){}
};

struct B{
    B(int x){this->x = x;}
    int x;
};

struct C{
    C(int x, double y){
        this->x = x;
        this->y = y;
    }
    C(int x){
        this->x = x;
        this->y = 0.0;
    }
    int x;
    double y;
};

int main()
{
    int i = 5;
    cout<<*Singleton<int>::get_Instance(i);


    Singleton<B>::get_Instance(std::move(i));

    Singleton<C>::get_Instance (6, 3.0);

    return 0;
}
