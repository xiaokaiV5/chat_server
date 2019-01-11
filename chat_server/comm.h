#pragma once
#ifndef __COMM_H__
#define __COMM_H__

#include <iostream>
#include "base_sock.h"
using namespace std;

#define MAX_onlineUser	1024 //Limit the number of online users
#define LISTEN_PORT		1000	//As tcp server, listen port 
#define LISTEN_QUEUE	5	//listen queue


class comm
{
public:
	comm();
	~comm();
	int comm_init();
	void *thread_accept();
	void *thread_process_accept(void * arg);
	void comm_listen();


public:
	int socket_AsS;//listen socket
	int onlineUser;
protected:
	
private:
	pthread_t tid;
};

#endif