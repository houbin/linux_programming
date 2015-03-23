#include <deque>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Test
{
    int a;
    int b;

    Test()
    {
        a = 0;
        b = 0;
    }

    Test(const Test &test)
    {
        printf("call Test &\n");
        a = test.a;
        b = test.b;
    }

    void operator=(const Test &test)
    {
        printf("call Test=\n");
        a = test.a;
        b = test.b;
    }
};

struct My
{
    int age;
    int number;
};


int GetAllTest(deque<Test> &test)
{
    int i = 0;
    for (; i < 10; i++)
    {
        Test temp;
        temp.a = i;
        temp.b = i;
        printf("call push_back\n");
        test.push_back(temp);
    }

    return 0;
}

int GenerateMy(My **my, int *size)
{
    My *my_temp = NULL;
    deque<Test> temp;

    printf("call getalltest before\n");
    GetAllTest(temp);
    printf("call getalltest after\n");


    int temp_size = temp.size();
    my_temp = new My[temp_size];

    int i = 0;
    deque<Test>::iterator iter = temp.begin();
    for(; iter != temp.end(); iter++)
    {
        Test temp;
        temp= *iter;

        printf("a of temp is %d, b of temp is %d\n", temp.a, temp.b);
        my_temp[i].age = temp.a;
        my_temp[i].number = temp.b;
        i++;
    }

    *my = my_temp;
    *size = temp_size;

    return 0;
}


int main()
{
    int size;
    My *my;

    GenerateMy(&my, &size);

    for (int i = 0; i < size; i++)
    {
        My temp = my[i];

        printf("seq %d, age of my is %d, number of my is %d\n", i, temp.age, temp.number);
    }

    return 0;
}
