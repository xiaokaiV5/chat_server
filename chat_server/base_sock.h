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
	int sock_fd;	//��ͻ���ͨ�ŵ��׽���
	struct sockaddr_in remote_addr;//remote user ip
private:

};

#endif // !__BASE_SOCK_H__
