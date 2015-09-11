#include <libjson/libjson.h>
#include <libjson/JSONOptions.h>
#include <string>
#include <iostream>

using namespace std;

#define SEND_CNT "sentcnt"
#define METHOD  "method"
#define METHOD_ONLINE "keep_online"
#define PARAM  "param"
#define DEV_ID "dev_id"
#define JK_MESSAGE_ID "mid"
#define JK_PROTO_VERSION "pv"
#define JK_CLIENT_TYPE          "ct"
#define JK_MESSAGE_TYPE     "method"
#define PROTO_VERSION "1.0"
#define METHOD_GET_SERVERS "get_server_ip"
#define JK_PARAM "param"
#define JK_ID "id"

string JsonGetServerIP(const int message_id, int nClientType, const std::string& id)
{
	JSONNode out;
	out.push_back(JSONNode(JK_MESSAGE_ID, message_id));
	out.push_back(JSONNode(JK_PROTO_VERSION, PROTO_VERSION));
	out.push_back(JSONNode(JK_CLIENT_TYPE, nClientType));
	out.push_back(JSONNode(JK_MESSAGE_TYPE, METHOD_GET_SERVERS));

	JSONNode paramArray;
	paramArray.set_name(JK_PARAM);		
	paramArray.push_back(JSONNode(JK_ID, id));
	out.push_back(paramArray);
	return out.write();
}

string make()
{
    JSONNode beacon_node;
    beacon_node.push_back(JSONNode(SEND_CNT, 111));
    beacon_node.push_back(JSONNode(METHOD, METHOD_ONLINE));

    JSONNode param_node(JSON_NODE);
    param_node.set_name(PARAM);
    param_node.push_back(JSONNode(DEV_ID, "A361"));

    beacon_node.push_back(param_node);

    return beacon_node.write();
}

void parse(string beacon_msg)
{
    JSONNode in;
    try
    {
        in = libjson::parse(beacon_msg);
    }
    catch(...)
    {
        return;
    }

    int sendcnt = in[SEND_CNT].as_int();
    string method = in[METHOD].as_string();
    JSONNode dev_id_node = in[PARAM].as_node();

    string dev_id = dev_id_node[DEV_ID].as_string();

    cout << "sendcnt is " << sendcnt << ", method is " << method << ", dev id is " << dev_id << endl;

    return;
}

int main()
{
    string beacon_msg = make();

    cout << "beacon msg is " << beacon_msg << endl;

    parse(beacon_msg);
    //
//    string get_server_ip = JsonGetServerIP(12345, 5, "A361");
//
//    cout << "get server ip is " << get_server_ip << endl;

    return 0;
}


