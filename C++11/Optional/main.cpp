#include <iostream>
#include "Optional.h"
using namespace std;

struct Mystruct{
    Mystruct(int a, double b){
        this->m_a = a;
        this->m_b = b;
    }
    int m_a;
    double m_b;
};

int main()
{
    Optional<string> a("a");
    Optional<string> b("a");
    Optional<string> c("a");

    c = a;



    Optional<Mystruct> op;
    op.Emplace(1,2.0);




    return 0;
}
