#include <deque>
#include <iostream>

using namespace std;

struct Test
{
    int a;
    int b;
};

int main()
{
    deque<Test*> test;

    for (int i = 0; i < 10; i++)
    {
        Test *t = new Test;
        t->a = i;
        t->b = i;

        test.push_back(t);
    }

    {
        deque<Test*>::iterator iter = test.begin();
        while(iter != test.end())
        {
            Test *t = *iter;
            cout << "a of test is " << t->a << ", b of test is " << t->b << endl;
            iter++;
        }
        cout << endl;
        cout << endl;
    }
    
    Test *t = test[5];
    t->a = 100;
    t->b = 100;

    {
        deque<Test*>::iterator iter = test.begin();
        while(iter != test.end())
        {
            Test *t = *iter;
            cout << "a of test is " << t->a << ", b of test is " << t->b << endl;
            iter++;
        }
    }

    return 0;
}
