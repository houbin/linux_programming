
#include "netlib.h"
#include "imconn.h"

void proxy_serv_callback(void* callback_data, uint8_t msg, uint32_t handle, void* pParam)
{
	if (msg == NETLIB_MSG_CONNECT)
	{
		CImConn* pConn = new CImConn();
		pConn->OnConnect(handle);
	}
	else
	{
		log("!!!error msg: %d", msg);
	}
}

int main()
{
    int ret = 0;
    ret = netlib_init();
    if (ret == NETLIB_ERROR)
    {
        printf("netlib_init error");
        return -1;
    }
    
    ret = netlib_listen("0.0.0.0", 9999, proxy_serv_callback, NULL);
    if (ret == NETLIB_ERROR)
    {
        printf("netlib_init error");
        return -1;
    }
    
    netlib_eventloop(10);

    return 0;
}
