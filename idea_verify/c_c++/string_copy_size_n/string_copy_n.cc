#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    string temp_string;

    char *temp_char = new char[100];
    memset(temp_char, 0, 100);

    for (int i = 0; i < 10; i++)
    {
        temp_char[i] = 'a';
    }

    for (int i = 20; i < 30; i++)
    {
        temp_char[i] = 'b';
    }

    temp_string.append(temp_char, 50);

    for(int i = 0; i < 50; i++)
    {
        cout << "temp_string[" << i << "] is " << temp_string[i] << endl;
    }

    cout << "sizeof temp_string is " << temp_string.size() << ", capacity is " << temp_string.capacity() << ", temp string is " << temp_string << endl;

    temp_string.clear();

    temp_string.append(temp_char, 40);
    for(int i = 0; i < 50; i++)
    {
        cout << "temp_string[" << i << "] is " << temp_string[i] << endl;
    }

    cout << "sizeof temp_string is " << temp_string.size() << ", capacity is " << temp_string.capacity() << ", temp string is " << temp_string << endl;

    return 0;
}
