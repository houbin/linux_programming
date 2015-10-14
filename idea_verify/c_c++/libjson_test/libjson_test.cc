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

void DecParamNode(JSONNode param_node)
{
    cout << "before param_node is " << param_node.write() << endl;
//    param_node.preparse();
    string temp_str = param_node.write();
    JSONNode temp_node = libjson::parse(temp_str);
    temp_node.preparse();

    JSONNode data_node = temp_node["param"].as_node();
    cout << "data_node is " << data_node.write() << endl;
    JSONNode data_node_2(JSON_NODE);
    int count = data_node.size();
    int i = 0;
    for(; i < count; i++)
    {
        JSONNode node = data_node[i];
        data_node_2.push_back(node);
    }

    cout << data_node_2.write() << endl;
    data_node_2.push_back(JSONNode("sendcnt", 0));

    cout << data_node_2.write() << endl;

{
    int count = data_node_2.size();
    cout << "count is " << count << endl;
    JSONNode aaa;
    aaa.set_name("aaa");
    int i = 0;
    for (; i < count; i++)
    {
        aaa.push_back(data_node_2[i]);
    }
    JSONNode aaa_temp;
    aaa_temp.push_back(aaa);
    aaa_temp.push_back(JSONNode("bbb", "bbb"));
    aaa_temp.push_back(JSONNode("ccc", "ccc"));
    JSONNode bbb;
    bbb.set_name("ddd");
    bbb.push_back(JSONNode("DDD", "DDD"));
    aaa_temp.push_back(bbb);
    cout << "aaa is " << aaa_temp.write() << endl;

    cout << "decode " << endl;

    aaa_temp.pop_back("ccc");

    //aaa_temp.push_back(JSONNode("hhhh", "bbb"));
    aaa_temp.pop_back("aaa");
    aaa_temp.pop_back("bbb");
    aaa_temp.pop_back("ddd");
    if (aaa_temp.empty())
    {
        cout << "aaa_temp is empty" << endl;
    }

    cout << "aaa_temp is " << aaa_temp.write() << endl;
}

    return;
}

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
    if (out.empty())
    {
        printf("out_node is empty\n");
    }
    else
    {
        printf("out_node is not empty\n");
    }

    JSONNode param_node;
    param_node.set_name("param_name");
    JSONNode name_node;
    name_node.push_back(JSONNode("name", "houbin"));

    param_node.push_back(name_node);
    //param_node.push_back(JSONNode("param_node", out.write()));
    //
    

    string test = out.write();
    cout << out.write() << endl;


    cout << endl;
    cout << "param_node is " << param_node.write() << endl;
    cout << endl;

    Parse(test);

    JSONNode empty_node;
    if (empty_node.empty())
    {
        printf("empty_node is empty\n");
    }
    else
    {
        printf("empty_node is not empty\n");
    }


    cout << "another test " << endl;
    JSONNode test_node;
    test_node.set_name("param");
    test_node.push_back(JSONNode("name", "houbin"));
    test_node.push_back(JSONNode("age", "30"));

    //DecParamNode(test_node);

    JSONNode test_node_2;
    test_node_2.push_back(test_node);

    DecParamNode(test_node_2);


    return 0;
}
