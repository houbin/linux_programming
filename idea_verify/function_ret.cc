#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Status
{
public:
    Status();
    Status(const Status& s);
    Status& operator=(const Status& arg);
};

Status::Status()
{
    cout << "call status" << endl;
}

Status::Status(const Status& s)
{
    cout << "call copy constructor" << endl;
}

Status& Status::operator=(const Status& arg)
{
    cout << "call operator=" << endl;
}

Status test()
{
    Status* s = new Status();

    return *s;
}

int main()
{
    Status b = test();
    return 0;
}
