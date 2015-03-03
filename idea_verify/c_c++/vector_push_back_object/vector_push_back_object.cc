#include <iostream>
#include <vector>

using namespace std;

class Test
{
public:
    int param_int_1_;

    Test()
    : param_int_1_(0)
    {
        cout << "call Test()" << endl;
    }

    ~Test()
    {
        cout << "call ~Test()" << endl;
    }

    Test(int a)
    {
        this->param_int_1_ = a;
        cout << "call Test(int a), param_int_1_ is " << this->param_int_1_ << endl;
    }
    
    Test(const Test &test)
    {
        this->param_int_1_ = test.param_int_1_;
        cout << "call Test(Test&), param_int_1_ is " << this->param_int_1_ << endl;
    }

    void operator=(const Test &test)
    {
        this->param_int_1_ = test.param_int_1_;
        cout << "call operator=, param_int_1_ is " << this->param_int_1_ << endl;
    }
};

void vector_push_back(vector<Test> &test)
{
    cout << "call function vector_push_back" << endl;
    for (int i = 0; i < 10; i++)
    {
        Test a(i);
        
        test.push_back(a);
    }

    Test b(17);
    test[17] = b;

    Test c(33);
    test[33] = c;

    int count = 0;
    vector<Test>::iterator iter = test.begin();
    for (iter; iter != test.end(); iter++)
    {
        cout << "seq " << count << ": iter->param_int_1_ = " << iter->param_int_1_ << endl;
    }
    cout << "call function vector_push_back end " << endl;
    return;
}

int main()
{
    vector<Test> test_vec;

    vector_push_back(test_vec);

    int count = 0;
    vector<Test>::iterator iter = test_vec.begin();
    for (iter; iter != test_vec.end(); iter++)
    {
        cout << "seq " << count << ": iter->param_int_1_ = " << iter->param_int_1_ << endl;
    }

    return 0;
}
