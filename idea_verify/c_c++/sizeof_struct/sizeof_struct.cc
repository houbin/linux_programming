#include <iostream>
#include <stdint.h>

using namespace std;

#pragma pack(4)
struct Test
{
    uint32_t a;
    uint32_t b;
    uint16_t c;
    bool d;
    bool e;
    uint32_t f;
    uint64_t g;
    uint64_t h;
    uint32_t i;
};
#pragma

int main()
{
    int a = sizeof(struct Test);

    cout << "sizeof a is " << a << endl;

    int b = sizeof(long);
    cout << "sizeof b is " << b << endl;

    return 0;
}

