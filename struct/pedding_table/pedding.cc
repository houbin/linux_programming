#include <map>
#include <iostream>

using namespace std;

int main()
{
    map<int, int> get;
    map<int, map<int, int>::iterator> pedding;

    typedef map<int, int> GET_T;
    typedef map<int, map<int, int>::iterator> PEDDING_T;

    int i = 0;
    for (i; i < 100; i++)
    {
        GET_T::value_type g_val(i, i);
        pair<GET_T::iterator, bool> ret = get.insert(g_val);
        GET_T::iterator iter = ret.first;

        PEDDING_T::value_type p_val(i, iter);
        pedding.insert(p_val);
    }

    i = 9;
    for (i; i < 100; i++)
    {
        if (i % 4 != 0)
        {
            continue;
        }
        
        {
            PEDDING_T::iterator p_iter = pedding.find(i);
            GET_T::iterator g_iter = p_iter->second;
            get.erase(g_iter);
            pedding.erase(i);
            cout << "pedding erase " << i << endl;
        }

        i--;
        {
            PEDDING_T::iterator p_iter = pedding.find(i);
            GET_T::iterator g_iter = p_iter->second;
            get.erase(g_iter);
            pedding.erase(i);
            cout << "pedding erase " << i << endl;
        }
        i++;
    }

    GET_T::iterator g_iter = get.begin();
    for (g_iter; g_iter != get.end(); g_iter++)
    {
        cout << "first is " << g_iter->first << endl;
    }

    return 0;
}
