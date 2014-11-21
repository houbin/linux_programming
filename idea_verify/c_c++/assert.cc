#include <assert.h>

void fun2()
{
    assert("abc");
}

void fun1()
{
    fun2();
}

int main()
{
    fun1();

    return 0;
}
