#include <string>
#include <iostream>

using namespace std;

class Test
{
public:
    string str;
};

int main()
{
    Test test;

    test.str = "abc";
    test.str.append("123456");
    test.str.append("78901234");

    cout << "size of test.str is " << sizeof(test) << endl;
    cout << "test.str is " << test.str << endl;

    return 0;
}
