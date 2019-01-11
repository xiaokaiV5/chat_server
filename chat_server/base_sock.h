#pragma once
#ifndef __BASE_SOCK_H__
#define __BASE_SOCK_H__

#include <netinet/in.h>
class base_sock
{
public:
	base_sock() {};
	~base_sock() {};
public:
	int sock_fd;	//与客户端通信的套接字
	struct sockaddr_in remote_addr;//远端user ip
private:

};

#endif // !__BASE_SOCK_H__
