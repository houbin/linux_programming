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
    JSONNode out;

    {
        JSONNode in;
        in.push_back(JSONNode("hou", "bin"));

        JSONNode param_node;
        param_node.set_name("param");
        param_node.push_back(JSONNode("abc", "123"));
        param_node.push_back(JSONNode("abc", "123"));
        param_node.push_back(JSONNode("abc", "123"));
        in.push_back(param_node);

        cout << "in is: " << in.write() << endl;
        cout << endl;

        JSONNode temp;
        temp = in["param"].as_node();

        cout << "temp is " << temp.write() << endl;
        out = temp.duplicate();

        JSONNode temp_2;
        in.swap(temp_2);
        temp.swap(temp_2);
    }

    {
        JSONNode in;
        in.push_back(JSONNode("123", "456"));

        JSONNode param_node;
        param_node.set_name("param");
        param_node.push_back(JSONNode("dfa", "234"));
        param_node.push_back(JSONNode("dfa", "323"));
        param_node.push_back(JSONNode("dfa", "123"));
        in.push_back(param_node);

        cout << "in is: " << in.write() << endl;
        cout << endl;
    }
    out.push_back(JSONNode("sent_cnt", "111"));
    cout << out.write() << endl;

    cout << endl;

    return 0;
}
