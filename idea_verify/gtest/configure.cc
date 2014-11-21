#include "configure.h"

int Configure::AddItem(std::string item)
{
    std::vector<std::string>::iterator iter = items.begin();

    for (iter = items.begin(); iter != items.end(); iter++)
    {
        if (item == *iter)
        {
            break;
        }
    }

    if (iter != items.end())
    {
        return iter - items.begin();
    }

    items.push_back(item);

    return items.size() - 1;
}

std::string Configure::GetItem(int index)
{
    if (index >= items.size())
    {
        return "";
    }
    else
    {
        return items[index];
    }
}

int Configure::Size()
{
    return items.size();
}

