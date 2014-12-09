#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Status
{
private:
public:
	int a;
	int b;

	Status()
	{
	    cout << "call status" << endl;
		a = 1;
		b = 2;
	}

	Status(int aa, int bb)
	{
		cout << "call status aa" << endl;
		a = aa;
		b = bb;
	}

	Status(const Status& s)
	{
	    cout << "call copy constructor" << endl;
		a = s.a;
		b = s.b;
	}

	Status& operator=(const Status& arg)
	{
	    cout << "call operator=" << endl;
		a = arg.a;
		b = arg.b;

		return *this;
	}
	
};


Status test()
{
	Status s;
	s.a = 99;
	s.b = 100;
    return s;
}

int main()
{
    Status b;
	b = test();

	cout << "b.a is " << b.a << ", b.b is " << b.b << endl;
    return 0;
}
