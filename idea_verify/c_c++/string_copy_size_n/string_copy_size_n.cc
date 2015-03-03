#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <stdlib.h>

using namespace std;

int main()
{
    char a[64] = {0};

    strncpy(a, "1234", 4);

    string test(a, 64);

    cout  << "a is " << a << ", test is " << test << endl;
    cout << "size of a is " << sizeof(a) << ", sizeof test is " << test.size() << ", capacity of test is " << test.capacity() << endl;


    string test_2(a);
    cout << ", sizeof test is " << test_2.size() << ", capacity of test is " << test_2.capacity() << endl;

    map<string, int> mymap;

    mymap.insert(make_pair(test, 5));
    mymap.insert(make_pair(test_2, 9));

    map<string, int>::iterator iter = mymap.begin();
    while (iter != mymap.end())
    {
        cout << "iter->first is " << (iter->first).c_str() << ", iter->second is " << iter->second << endl;
        iter++;
    }

    char *my_char;
    my_char = (char *)malloc(101);
    memset(my_char, 0, 101);
    memset(my_char, 'a', 100);

    string my_str(my_char);
    cout << "before change, my_char is " << my_char << ", my_str is " << my_str << endl;

    memset(my_char, 'b', 100);
    cout << "before change, my_char is " << my_char << ", my_str is " << my_str << endl;

    return 0;
}
