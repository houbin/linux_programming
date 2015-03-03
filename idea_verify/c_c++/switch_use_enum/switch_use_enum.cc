#include <iostream>
using namespace std;

enum ENUM_COLOR
{
    ENUM_RED = 0,
    ENUM_GREEN = 1,
    ENUM_YELLOW = 2,
    ENUM_BLACK = 3
};

int main()
{
    ENUM_COLOR color = ENUM_RED;
    
    switch(color)
    {
        case ENUM_RED:
            cout << "color is red" << endl;
            break;
        
        case ENUM_GREEN:
            cout << "color is green" << endl;
            break;
        case ENUM_YELLOW:
            cout << "color is yellow" << endl;
            break;
        
        case ENUM_BLACK:
            cout << "color is black" << endl;
            break;

        default:
            cout << "error color" << endl;
    }

    return 0;
}
