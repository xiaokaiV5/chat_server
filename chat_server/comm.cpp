#include <iostream>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <thread>

#include "comm.h"
#include "user.h"


comm::comm()
{
	comm_init();

	this->socket_AsS = 0;

}

comm::~comm()
{

}

int comm::comm_init()
{
	//int server_sockfd;//服务器端套接字
	struct sockaddr_in my_addr;   //服务器网络地址结构体

	memset(&my_addr, 0, sizeof(my_addr)); //数据初始化--清零
	my_addr.sin_family = AF_INET; //设置为IP通信
	my_addr.sin_addr.s_addr = INADDR_ANY;//服务器IP地址--允许连接到所有本地地址上
	my_addr.sin_port = htons(LISTEN_PORT); //服务器端口号

	/*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
	this->socket_AsS = socket(PF_INET, SOCK_STREAM, 0);
	if (this->socket_AsS < 0)
	{
		perror("socket error");
		return 1;
	}
	//

	/*将套接字绑定到服务器的网络地址上*/
	if (bind(this->socket_AsS, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("bind error");
		return 1;
	}

	/*监听连接请求--监听队列长度为5*/
	if (listen(this->socket_AsS, LISTEN_QUEUE) < 0)
	{
		perror("listen error");
		return 1;
	};


	cout << "create thread to accept tcp client accept!" << endl;
	//pthread_create(&this->tid, NULL, this->thread_accept, NULL);====
	return 0;
}

void* comm::thread_accept()
{
	struct sockaddr_in remote_addr; //客户端网络地址结构体
	socklen_t sin_size;
	pthread_t tid;
	sin_size = sizeof(struct sockaddr_in);
	int sock_client(0);
	//int client_sock = *(int*)(arg);

	while (1)
	{
		if ((sock_client = accept(this->socket_AsS, (struct sockaddr *)&remote_addr, &sin_size)) < 0)
		{
			perror("accept error!\n");
		}
		else
		{
			printf("accept client %s/n", inet_ntoa(remote_addr.sin_addr));
			//创建线程或进程对此用户进行密码信息等检测！！！
			//thread_create(&tid, NULL, , NULL);
		}
	}

	return NULL;
}

void* comm::thread_process_accept(void  *arg)
{
	userInfo *user = new userInfo();
	user->sock_fd = *(int *)(arg);
	user->tid_work = std::this_thread::get_id();

	//书写接收函数，对账号和密码与sqlite数据库中的数据进行比对验证。验证通过择进行授权。


	return NULL;
}
