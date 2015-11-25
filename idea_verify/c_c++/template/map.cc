#include <map>
#include <iostream>
#include <stdint.h>
#include <assert.h>

using namespace std;


int main()
{
    multimap< int, pair<int, int> > schedule;
    map<int, multimap<int, pair<int, int> >::iterator> events;

    typedef multimap<int, pair<int, int> > scheduled_map_t;
    typedef map<int, multimap<int, pair<int, int> >::iterator> event_map_t;

    int time;
    int mid;
    int event;

    int i = 0;
    for (; i < 10; i++)
    {
        time = i;
        mid = i + 1;
        event = i + 2;

        scheduled_map_t::iterator iter = schedule.insert(make_pair(time, make_pair(mid, event)));
        pair<event_map_t::iterator, bool> ret = events.insert(make_pair(mid, iter));
        assert(ret.second);
    }

    while(!schedule.empty())
    {
        scheduled_map_t::iterator iter = schedule.begin();
        int time = iter->first;
        int mid = iter->second.first;
        int event = iter->second.second;

        cout << "time " << time << ", (" << mid << ", " << event << ")" << endl;

        event_map_t::iterator e_iter = events.find(mid);
        assert(e_iter != events.end());

        events.erase(e_iter);
        schedule.erase(iter);
    }

    cout << "after scan" << endl;

    int s_size = schedule.size();
    int e_size = events.size();

    cout << "size of schedule " << s_size << ", size of event " << e_size << endl;

    return 0;
}
