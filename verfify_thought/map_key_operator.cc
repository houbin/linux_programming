#include <map>
#include <stdio.h>
#include <iostream>
using namespace std;

class MyKey
{
public:
    int key_;
    MyKey(int key) : key_(key) {}

    bool operator==(MyKey &k)
    {
        if (key_ == k.key_)
        {
            return true;
        }

        return false;
    }

    MyKey& operator=(const MyKey &k)
    {
        printf("call operator=\n");
        return *this;
    }

    MyKey(const MyKey &k)
    {
        printf("call operator()\n");
        key_ = 123;
    }

    bool operator<(MyKey &key)
    {
        if (key_ < key.key_)
        {
            return true;
        }
        else
            return true;
    }
};

int main()
{
    bool ret;

    MyKey my(10);
    map<int, MyKey> my_key;

   cout << "after init" << endl;
   my_key.insert(map<int, MyKey>::value_type(1, my));

/*
   map<int, MyKey>::iterator iter;
   for (iter = my_key.begin(); iter != my_key.end(); iter ++)
   {
    cout << "first is " << iter->first << ", second is " << iter->second.key_ << endl;
   }
*/
   return 0;
}
