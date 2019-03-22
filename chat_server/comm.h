#pragma once
#ifndef __COMM_H__
#define __COMM_H__

#include <iostream>
#include "base_sock.h"
#include "user.h"
using namespace std;

#define MAX_onlineUser	1024 //Limit the number of online users
#define LISTEN_PORT		1001	//As tcp server, default listen port 
#define LISTEN_QUEUE	5	//listen queue

#define d_data_len	4096	//the max length of one message.
 
void send_data(userInfo * user);

class comm
{
public:
	comm();
	~comm();
	int comm_init();
	int comm_init(uint16_t port);

	void *thread_accept();
	bool thread_processAccept(int sock_cli);
	void process_accept(void * arg);
	void message_process(userInfo *user);
	friend void send_data(userInfo *user);
	friend void send_data(int sockfd, userInfo * user);

public:
	int socket_AsS;//listen socket
	int socket_AsS_c;	//accept client socket filled
	int onlineUser;
protected:
	
private:
	pthread_t tid;
};

#endif