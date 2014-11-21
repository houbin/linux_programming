#include <vector>
#include <string>

class Configure
{
private:
    std::vector<std::string> items;
public:
    int AddItem(std::string item);
    std::string GetItem(int index);
    int Size();
};
