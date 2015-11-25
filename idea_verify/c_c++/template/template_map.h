
#include <map>

using namespace std;

template<typename T>
bool operator<(const T &a, const T &b)
{
    if (a > b)
    {
        return true;
    }

    return false;
}
template<typename T>
class Test
{
public:
    multimap< int, pair<T, int> > schedule;
    map< T, multimap<int, pair<T, int> >::iterator> events;

    void Insert(int time, T mid, int event);
    void Remove(T mid);
};

