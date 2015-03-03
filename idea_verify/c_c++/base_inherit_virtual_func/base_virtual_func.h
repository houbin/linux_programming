#include <iostream>
using namespace std;

class Base
{
public:
    virtual void f()
    {
        cout << "Base::f()" << endl;
    }

    virtual void g()
    {
        cout << "Base::g()" << endl;
    }

    virtual void h()
    {
        cout << "Base::h()" << endl;
    }
};

class Derive : public Base
{
public:
    virtual void f()
    {
        cout << "Derive::f()" << endl;
    }

    virtual void f1()
    {
        cout << "Derive::f1()" << endl;
    }

    virtual void g1()
    {
        cout << "Derive::g1()" << endl;
    }

    void h1()
    {
        cout << "Derive::h1()" << endl;
    }

    static void i1()
    {
        cout << "Derive::i1()" << endl;
    }
};
