/*
 * imconn.h
 *
 *  Created on: 2013-6-5
 *      Author: ziteng
 */

#ifndef IMCONN_H_
#define IMCONN_H_

#include "netlib.h"
#include "util.h"
#include "buffer_loop.hpp"
#include <string>
#include <map>

using namespace std;

#define SERVER_HEARTBEAT_INTERVAL	5000
#define SERVER_TIMEOUT				30000
#define CLIENT_HEARTBEAT_INTERVAL	30000
#define CLIENT_TIMEOUT				120000
#define MOBILE_CLIENT_TIMEOUT       60000 * 5
#define READ_BUF_SIZE	2048

void imconn_callback(void* callback_data, uint8_t msg, uint32_t handle, void* pParam);
void ReadPolicyFile();

class CImConn;
typedef map<net_handle_t, CImConn*> ConnMap_t;
extern ConnMap_t g_connections;

class CImConn : public CRefObject
{
public:
	CImConn();
	virtual ~CImConn();

	bool IsBusy() { return m_busy; }
	int Send(void* data, int len);

	virtual void OnConnect(net_handle_t handle) 
    {
        m_handle = handle;
        g_connections.insert(make_pair(handle, this));
        
        netlib_option(handle, NETLIB_OPT_SET_CALLBACK, (void*)imconn_callback);
        netlib_option(handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)&g_connections);
    }
	virtual void OnConfirm() { printf("CImConn::OnConfirm\n");}
	virtual void OnRead();
	virtual void OnWrite();
	virtual void OnClose() 
    {
    // printf("CImConn::OnClose\n");
    }
	virtual void OnTimer(uint64_t curr_tick) {}
    virtual void OnWriteCompelete() 
    { 
        //printf("OnWriteComplete\n");
        }

protected:
	net_handle_t	m_handle;
	bool			m_busy;

	string			m_peer_ip;
	uint16_t		m_peer_port;
	CSimpleBuffer	m_in_buf;
	CSimpleBuffer	m_out_buf;

	bool			m_policy_conn;
	uint32_t		m_recv_bytes;
	uint64_t		m_last_send_tick;
	uint64_t		m_last_recv_tick;
    uint64_t        m_last_all_user_tick;
};


#endif /* IMCONN_H_ */
