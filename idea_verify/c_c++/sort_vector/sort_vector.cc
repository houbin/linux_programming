#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>

using namespace std;

struct Item
{
    int a;
};

bool operator<(Item a, Item b)
{
    if (a.a < b.a)
    {
        return true;
    }

    return false;
}

int main()
{
    int i = 0;
    int random = 0;
    vector<Item> unsort_item_vec;

    for (i; i < 10; i++)
    {
        random = rand();
        Item temp;
        temp.a = random;
        unsort_item_vec.push_back(temp);
    }

    i = 0;
    vector<Item>::iterator iter;
    for(iter = unsort_item_vec.begin(); iter != unsort_item_vec.end(); iter++)
    {
        printf("seq %d, a of item is %d\n", i, iter->a);
        i++;
    }

    sort(unsort_item_vec.begin(), unsort_item_vec.end());

    i = 0;
    for(iter = unsort_item_vec.begin(); iter != unsort_item_vec.end(); iter++)
    {
        printf("seq %d, a of item is %d\n", i, iter->a);
        i++;
    }

    return 0;
}
