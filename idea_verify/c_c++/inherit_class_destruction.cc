#include <stdio.h>

class Base
{
public:
    Base()
    {
        printf("call Base()\n");
    }

    ~Base()
    {
        printf("call ~Base\n");
    }
};

class Inherit : public Base
{
public:
    Inherit()
    {
        printf("call inherit()\n");
    }

    ~Inherit()
    {
        printf("call ~Inherit\n");
    }
};


int main()
{
    Inherit i;

    return 0;
}
