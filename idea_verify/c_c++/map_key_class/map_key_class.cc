#include <iostream>
#include <map>

using namespace std;

class AAA
{
public:
    int b;
    int a;
    AAA(int aaa, int bbb) : a(aaa), b(bbb) {}

    bool operator< (const AAA &b) const
    {
        return (this->a < b.a);
    }
};

/*
bool operator<(const AAA &a, const AAA &b)
{
    return (a.a < b.a);
}
*/

class Test
{
public:
    map<AAA, int> class_map;

};

int main()
{
    AAA aa(5, 6);
    AAA bb(10, 11);
    AAA cc(7, 8);
    AAA dd(100, 101);
    AAA ee(85, 86);

    Test test;
    test.class_map.insert(map<AAA, int>::value_type(aa, 5));
    test.class_map.insert(map<AAA, int>::value_type(bb, 5));
    test.class_map.insert(map<AAA, int>::value_type(cc, 5));
    test.class_map.insert(map<AAA, int>::value_type(dd, 5));
    test.class_map.insert(map<AAA, int>::value_type(ee, 5));

    map<AAA, int>::iterator iter = test.class_map.begin();
    for (iter = test.class_map.begin(); iter != test.class_map.end(); iter++)
    {
        cout << "iter->first is " << iter->first.a << ", iter->second is " << iter->second << endl;
    }

    AAA ff(85, 1);
    iter = test.class_map.find(ff);
    if (iter != test.class_map.end())
    {
        cout << "we found key = 85: iter->first is " << iter->first.a << ", iter->second is " << iter->second << endl;
    }
    else
    {
        cout << "we don't find key = 85" << endl;
    }

    AAA gg(101, 1123123);
    iter = test.class_map.find(gg);
    if (iter != test.class_map.end())
    {
        cout << "we found key = 123, iter->first is " << iter->first.a << ", iter->second is " << iter->second << endl;
    }
    else
    {
        cout << "we don't find key = 123" << endl;
    }

    return 0;
}
