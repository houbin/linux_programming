#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include "base_virtual_func.h"

using namespace std;

int main()
{
    typedef void (*FUNC)(void);
    FUNC pFunc;
    Base *b = new Derive();

    cout << "sizeof base is " << sizeof(Base) << endl;
    cout << "sizeof derive is " << sizeof(Derive) << endl;
    cout << "虚函数表地址为：" << b << endl;
    cout << "第一个虚函数地址为：" << (int64_t *)*(int64_t *)(b) << ", 内容为: " << *(int64_t*)*(int64_t*)b << endl;
    cout << "第二个虚函数地址为：" << ((int64_t *)*(int64_t *)(b) + 1) << ", 内容为：" << *((int64_t*)*(int64_t*)b + 1) <<endl;
    cout << "第三个虚函数地址为：" << ((int64_t *)*(int64_t *)(b) + 2) << ", 内容为：" << *((int64_t*)*(int64_t*)b + 2) <<endl;
    cout << "第四个虚函数地址为：" << ((int64_t *)*(int64_t *)(b) + 3) << ", 内容为：" << *((int64_t*)*(int64_t*)b + 3) <<endl;

    pFunc = ((FUNC)(*(int64_t *)(*(int64_t *)b)));
    int count = 1;
    while (pFunc != NULL)
    {
        pFunc();
        pFunc = (FUNC)*((int64_t *)(*(int64_t *)b) + count);
        cout << "pFunc is " <<  *((int64_t *)(*(int64_t *)b) + count) << endl;
        count++;
    }

    printf("address of h1 is %p\n", &Derive::h1);
    printf("address of i1 is %p\n", &Derive::i1);

    return 0;
}
