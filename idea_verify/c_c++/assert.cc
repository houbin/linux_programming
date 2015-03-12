#include <assert.h>

void fun2()
{
    assert("abc" == 0);
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
