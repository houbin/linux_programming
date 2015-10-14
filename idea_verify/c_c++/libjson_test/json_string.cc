#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libjson/libjson.h>
#include <libjson/JSONOptions.h>
#include "libjson/_internal/Source/JSONNode.h"
#include <stdio.h>

using namespace std;

int main()
{
    JSONNode in, out;
    char buffer[256] = {0};

    int i = 0;
    for(; i < 256; i++)
    {
        buffer[i] = i;
    }

    string s(buffer, 256);

    in.push_back(JSONNode("hou", "bin"));
    in.push_back(JSONNode("str", s));

    cout << "in is: " << in.write() << endl;
    cout << endl;

    string in_str = in.write();
    cout << "json total length is " << in_str.size() << endl;

    out = libjson::parse(in_str);
    out.preparse();

    string out_str = out["str"].as_string();
    const char *data = out_str.c_str();
    int size = out_str.size();

    cout << out_str << endl;
    cout << "print ascii: (";
    for(i = 0; i < size; i++)
    {
        cout << data[i] << " ";
    }
    cout << ")" << endl;

    cout << endl;

    return 0;
}
