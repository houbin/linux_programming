#include <iostream>
#include <stdint.h>

using namespace std;

int main()
{
    int32_t ret = -322348424;

    uint32_t uret = (uint32_t)ret;

    int32_t result = (int32_t)uret;

    cout << "uret is " << uret << ", result is " << result << endl;

    return 0;
}
