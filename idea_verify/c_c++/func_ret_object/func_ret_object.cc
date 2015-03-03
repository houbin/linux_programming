#include<iostream>
#include <stdio.h>
#include <string.h>

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
    TestConstructor(const TestConstructor& testObj)
    {
        std::cout<<"TestConstructor(const TestConstructor&)"<<std::endl;
    }
    TestConstructor& operator = (const TestConstructor& testObj)
    {
        std::cout<<"TestConstructor& operator = (const TestConstructor& testObj)"<<std::endl;
        return *this;
    }
};
TestConstructor testFunc()
{
    TestConstructor testInFunc("testFunc");  //3、调用TestConstructor() 生成对象testInFunc
    return testInFunc;           //4、调用TestConstructor(const TestConstructor&) 生成临时对象
}

int main()
{
    TestConstructor test = testFunc();

    std::cout << "aaa of test is " << test.aaa << std::endl;
    return 0;    
}
