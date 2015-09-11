
std::string CNetDataLayer::JsonGetServerIP(const int message_id,ClientType nClientType,const std::string& id)
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
