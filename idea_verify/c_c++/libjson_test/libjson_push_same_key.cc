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
    JSONNode param_node;

    param_node.push_back(JSONNode("aaa", "111"));
    param_node.push_back(JSONNode("aaa", "111"));

    cout << "string of param_node is " << param_node.write() << endl;

    return 0;
}

