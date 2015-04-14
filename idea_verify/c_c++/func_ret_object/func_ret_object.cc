#include<iostream>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

class TestConstructor
{
public:
    char aaa[30];

    TestConstructor()
    {
        std::cout<<"TestConstructor()"<<std::endl;
    }

    TestConstructor(char *test)
    {
        memset(aaa, 0, 30);
        strncpy(aaa, test, 29);
    }

    ~TestConstructor()
    {
        std::cout<<"~TestConstructor()"<<std::endl;
    }

    TestConstructor(TestConstructor& testObj)
    {
        std::cout<<"TestConstructor(const TestConstructor&)"<<std::endl;
    }

    TestConstructor& operator = (TestConstructor& testObj)
    {
        std::cout<<"TestConstructor& operator = (const TestConstructor& testObj)"<<std::endl;
        return *this;
    }
};

TestConstructor testFunc()
{
    char temp[64] = {0};
    strcpy(temp, "test func");
    TestConstructor testInFunc(temp);  //3、调用TestConstructor() 生成对象testInFunc
    return testInFunc;           //4、调用TestConstructor(const TestConstructor&) 生成临时对象
}

int main()
{
    char temp[64] = {0};
    strcpy(temp, "aaa");
    TestConstructor test(temp);

    cout << "step 1" << endl;
    TestConstructor aaa(test);

    cout << "step 2" << endl;
    TestConstructor bbb;

    cout << "step 3" << endl;
    TestConstructor ccc = bbb;

    cout << "step 4" << endl;
    aaa = bbb;

    cout << "step 5" << endl;
    map<int, TestConstructor> test_map;
    cout << "step 6" << endl;
    cout << "step 7" << endl;
    map<int, TestConstructor>::iterator iter = test_map.find(1);
    cout << "step 8" << endl;
    iter->second = bbb;
    return 0;    
}
