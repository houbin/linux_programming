#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libjson/libjson.h>
#include <libjson/JSONOptions.h>
#include "libjson/_internal/Source/JSONNode.h"

using namespace std;

/*
int main()
{
    JSONNode node(JSON_NODE);
    node.push_back(JSONNode("houbin", "abc"));

    JSONNode array(JSON_ARRAY);
    array.set_name("list");
    
    JSONNode addr(JSON_NODE);
    addr.push_back(JSONNode("ip", "127.0.0.1"));
    addr.push_back(JSONNode("port", "15000"));

    string addr_str = addr.write();
    cout << "addr_str is " << addr_str << endl;

    array.push_back(JSONNode("", addr_str));
    node.push_back(array);

    string temp = node.write();

    cout << temp << endl;

    return 0;
}
*/

struct LoadItem
{
    struct sockaddr_in load_client_addr;
};

int JsonBuildAddressListResp(vector<LoadItem> &sorted_short_conn_vec, vector<LoadItem> &sorted_long_conn_vec, JSONNode &out_)
{
    out_.push_back(JSONNode("mid", 123));
    out_.push_back(JSONNode("method", "get_something"));
    out_.push_back(JSONNode("rt", 0));

    JSONNode param;
    param.set_name("param");

    JSONNode list_node(JSON_ARRAY);
    list_node.set_name("list");
	vector<LoadItem>::iterator short_conn_iter = sorted_short_conn_vec.begin();
	for (short_conn_iter; short_conn_iter != sorted_short_conn_vec.end(); short_conn_iter++)
	{
		string temp(inet_ntoa(short_conn_iter->load_client_addr.sin_addr));
		int port = htons(short_conn_iter->load_client_addr.sin_port);

		JSONNode addr_node(JSON_NODE);
		addr_node.push_back(JSONNode("ip", temp));
		addr_node.push_back(JSONNode("port", port));

		list_node.push_back(addr_node);
	}

    JSONNode list_online(JSON_ARRAY);
	list_online.set_name("list_online");
	vector<LoadItem>::iterator long_conn_iter = sorted_long_conn_vec.begin();
	for (long_conn_iter; long_conn_iter != sorted_long_conn_vec.end(); long_conn_iter++)
	{
		string temp(inet_ntoa(long_conn_iter->load_client_addr.sin_addr));
		int port = htons(long_conn_iter->load_client_addr.sin_port);

		JSONNode addr_node(JSON_NODE);
		addr_node.push_back(JSONNode("ip", temp));
		addr_node.push_back(JSONNode("port", port));

		list_online.push_back(addr_node);

        //list_online.push_back(JSONNode("ip", temp));
		//list_online.push_back(JSONNode("port", port));
	}

    param.push_back(list_node);
    param.push_back(list_online);

	out_.push_back(param);

	return 0;
}

void Parse(string msg)
{

    JSONNode msg_node = libjson::parse(msg.c_str());
    msg_node.preparse();

    JSONNode param_node = msg_node["param"].as_node();

    JSONNode list_node(JSON_ARRAY);
    list_node = param_node["list_online"].as_node();

    int size = list_node.size();

    JSONNode node_0 = list_node[0];
    string ip = node_0["ip"].as_string();

    return ;
}

int main()
{
    JSONNode out;

    vector<LoadItem> short_conn_vec;
    vector<LoadItem> long_conn_vec;

    for (int i = 0; i < 3; i++)

    {
        LoadItem temp;
        temp.load_client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        temp.load_client_addr.sin_port = htons(i + 1234);

        short_conn_vec.push_back(temp);
        long_conn_vec.push_back(temp);
    }

    JsonBuildAddressListResp(short_conn_vec, long_conn_vec, out);

    string test = out.write();
    cout << out.write() << endl;

    Parse(test);

    return 0;
}
