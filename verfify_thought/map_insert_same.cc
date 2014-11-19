#include <map>
#include <iostream>
using namespace std;

map<int, int> testMap;
int main()
{
    testMap.insert(pair<int, int>(10, 10));
    testMap.insert(pair<int, int>(20, 20));
    testMap.insert(pair<int, int>(30, 30));
    testMap.insert(pair<int, int>(40, 40));

    map<int, int>::iterator iter;
    for(iter = testMap.begin(); iter != testMap.end(); iter++)
    {
        cout << iter->first << " -> " << iter->second << endl;
    }

    testMap.insert(pair<int, int>(10, 20));
    for(iter = testMap.begin(); iter != testMap.end(); iter++)
    {
        cout << iter->first << " -> " << iter->second << endl;
    }

    return 0;
}
