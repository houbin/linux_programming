#include <iostream>

using namespace std;

class StreamInfo
{
public:
    char stream_type_[32];
    char sid_[32];
    char protocol_[16];
    bool main_stream;
    bool sub_stream;
    char main_stream_rstp_addr[64];
    char sbu_stream_rstp_addr[64];
    char id_[64];        //云视通id
    char ip_[16];        
    char port [8];
    char name_[64];
    char channelcnt_[8];
    char channel_id_[8];
    char user_name_[32];
    char user_passwd_[32];
    char stream_server_ip_[16];
    char stream_server_port_[8];
    char stream_server_channel_id_[8];
};

int main()
{
    StreamInfo info;

    cout << "sizeof info is " << sizeof(info) << endl;
    cout << "sizeof clas streaminfo is " << sizeof(StreamInfo) << endl;
    cout << "sizeof info.user_passwd_ is " << sizeof(info.user_passwd_) << endl;

    return 0;
}
