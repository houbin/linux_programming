#include <stdio.h>

class Parent
{
public:
    void SayHello()
    {
        printf("parent say hello\n");
    }

    void SayGoodBye()
    {
        printf("parent say goodbye\n");
    }
};

class Child : public Parent
{
public:
    void SayHello()
    {
        printf("child say hello\n");
    }

    void SayGoodBye()
    {
        printf("child say goodbye\n");
    }
};

int main()
{
    Parent *p = new Child();

    p->SayHello();
    p->SayGoodBye();

    return 0;
}
