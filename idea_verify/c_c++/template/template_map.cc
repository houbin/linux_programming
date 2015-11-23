#include <map>
#include <iostream>
#include <stdint.h>
#include <assert.h>
#include "template_map.h"

using namespace std;

template<typename T>
typedef multimap<int, pair<T, int> > scheduled_map_t;
template<typename T>
typedef map<T, multimap<int, pair<T, int> >::iterator> event_map_t;

template<typename T>
void Test::Insert(int time, T mid, int event)
{
    cout << "insert: "<< "time " << time << ", (" << mid << ", " << event << ")" << endl;
    scheduled_map_t::iterator iter = schedule.insert(make_pair(time, make_pair(mid, event)));
    pair<event_map_t::iterator, bool> ret = events.insert(make_pair(mid, iter));
    assert(ret.second);

    return;
}

template<typename T>
void Test::Remove(T mid)
{
    event_map_t::iterator e_iter = events.find(mid);
    assert(e_iter != events.end());

    scheduled_map_t::iterator s_iter = e_iter->second;
    assert(s_iter != schedule.end());

    events.erase(e_iter);
    schedule.erase(iter);
}

int main()
{
    Test<int> test;

    int time;
    int mid;
    int event;

    int i = 0;
    for (; i < 10; i++)
    {
        time = i;
        mid = i + 1;
        event = i + 2;

        test.Insert(time, mid, event);
        cout << "insert: "<< "time " << time << ", (" << mid << ", " << event << ")" << endl;
    }

    for (i = 1; i < 11; i++)
    {
        cout << "Remove: mid " << mid << endl;
        test.Remove(i);
    }

    cout << "after remove " << endl;

    cout << "size of schedule " << s_size << ", size of event " << e_size << endl;

    return 0;
}
