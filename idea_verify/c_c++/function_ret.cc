#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Status
{
private:
public:
    int a;
    Status()
    {
    
    }

	Status(int a)
	{
        this->a = a;
	    cout << "call status" << ", a is " << a << endl;
	}

	Status(int aa, int bb)
	{
		cout << "call status aa" << endl;
	}

	Status(const Status& s)
	{
	    cout << "call copy constructor" << ", a is " << a << endl;
	}

	Status& operator=(const Status& arg)
	{
        this->a = arg.a;
	    cout << "call operator=" << ", a is " << a << endl;

		return *this;
	}

    int GetA()
    {
        return a;
    }
};

class Derive
{
private:
    Status status_;

public:
    Derive(Status &status)
    {
        status_ = status;
    }

    int GetA()
    {
        return status_.GetA();
    }
};

Status test()
{
	Status s(10101010);
    return s;
}

int test_2(Status s)
{
    printf("test_2: a of status s is %d\n", s.a);

    return 0;
}

int main()
{
    Status b(5);
    b = test();


    Derive derive(b);
    cout << "a of b is " << derive.GetA() << endl;

    cout << "test function parameter" << endl;

    test_2(b);
    return 0;
}
