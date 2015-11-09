#include <iostream>
#include <unistd.h>

using namespace std;

struct Test
{
    int *a;
    char *b;
};

int main()
{
    cout << "before new Test" << endl;
    sleep(15);
    Test *t = new Test;
    cout << "after new Test" << endl;
    sleep(15);

    delete t;
    cout << "after delete" << endl;
    sleep(15);

    return 0;
}
