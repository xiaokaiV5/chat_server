#include <iostream>

#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <thread>

#include "comm.h"
#include "user.h"
#include "define.h"
#include "online_user_operate.h"

comm::comm()
{
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
		myCout << "socket error" << endl;
		return 1;
	}
	//

	/*将套接字绑定到服务器的网络地址上*/
	if (bind(this->socket_AsS, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) < 0)
	{
		myCout << "bind error Reason:" << strerror(errno) << endl;
		return 1;
	}

	/*监听连接请求--监听队列长度为5*/
	if (listen(this->socket_AsS, LISTEN_QUEUE) < 0)
	{
		myCout << "listen error" << endl;
		return 1;
	};


	myCout << "create thread to accept tcp client accept!" << endl;
	//pthread_create(&this->tid, NULL, this->thread_accept, NULL);
	return 0;
}

int comm::comm_init(uint16_t port)
{

	//int server_sockfd;//服务器端套接字
	struct sockaddr_in my_addr;   //服务器网络地址结构体

	memset(&my_addr, 0, sizeof(my_addr)); //数据初始化--清零
	my_addr.sin_family = AF_INET; //设置为IP通信
	my_addr.sin_addr.s_addr = INADDR_ANY;//服务器IP地址--允许连接到所有本地地址上
	my_addr.sin_port = htons(port); //服务器端口号

	/*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
	this->socket_AsS = socket(PF_INET, SOCK_STREAM, 0);
	if (this->socket_AsS < 0)
	{
		myCout << "socket error" << endl;
		return 1;
	}
	int reuse = 1;
	if (setsockopt(this->socket_AsS, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(int)) < 0)
	{
		cout << "setsockopt error, Reason:" << strerror(errno) << endl;
		return 1;
	}

	/*将套接字绑定到服务器的网络地址上*/
	if (bind(this->socket_AsS, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) < 0)
	{
		myCout << "bind error" << endl;
		return 1;
	}

	/*监听连接请求--监听队列长度为5*/
	if (listen(this->socket_AsS, LISTEN_QUEUE) < 0)
	{
		myCout << "listen error" << endl;
		return 1;
	};


	myCout << "create thread to accept tcp client accept!" << endl;
	//pthread_create(&this->tid, NULL, this->thread_accept, NULL);
	return 0;
}


void* comm::thread_accept()
{
	struct sockaddr_in remote_addr; //客户端网络地址结构体
	socklen_t sin_size;
	pthread_t tid;
	sin_size = sizeof(remote_addr);
	int sock_client(0);
	//int client_sock = *(int*)(arg); 
	int i = 1;
	while (1)
	{
		if ((sock_client = accept(this->socket_AsS, (struct sockaddr *)&remote_addr, &sin_size)) < 0)
		{
			myCout << "accept error, this->socket_AsS: " << this->socket_AsS << "Reason:" << strerror(errno) << endl;
		}
		else
		{
			myCout << "accept client " << inet_ntoa(remote_addr.sin_addr) << endl;
			this->socket_AsS_c = sock_client;
			//创建线程或进程管理用户注册上线消息转发等行为
			this->thread_processAccept(sock_client);
		}
	}

	return NULL;
}
typedef void* (*FUNC)(void*);//定义FUNC类型是一个指向函数的指针，该函数参数为void*，返回值为void*
bool comm::thread_processAccept(int sock_cli)
{
	myCout << "thread_processAccept" << endl;

	FUNC callback = (FUNC)&comm::process_accept;//强制转换func()的类型

	int ret = pthread_create(&this->tid, NULL, callback, this);
	if (ret != 0)
		return false;
	else
		return true;

}

void comm::process_accept(void *arg)
{
	userInfo *user = new userInfo();//在用户下线的时候进行释放=======待释放
	user->sock_fd = this->socket_AsS_c;
	user->tid_work = std::this_thread::get_id();
	myCout << "Create thread id " << user->tid_work << " sock_cli " << user->sock_fd << endl;

	//char data[d_data_len] = { 0 };
	//char *p = &data;
	int len = 0;
	while (1)
	{
		len = read(user->sock_fd, &user->data, sizeof(user->data));
		if (len < 0)
		{
			myCout << "read message error!" << endl;
			break;
		}
			
		else if (len == 0)
		{
			cout << "user close the socket !" << endl;
			close(user->sock_fd);
			//should delete user.
			delete user;
			user = nullptr;
			break;
		}
		else
		{
			myCout << "recv message size:" << len << endl;

			message_process(user);
		}
	}
	delete user;
	user = nullptr;
}

void comm::message_process(userInfo *user)
{
	ts_userInfo info;
	memset(&info, 0, sizeof(ts_userInfo));
	
	switch (user->data.cmd)
	{
	case CMD_LOGIN:
		cout << "user login !";
		user->data.cmd = user->user_login(db.mysql, info);
		if (user->data.cmd == D_USER_ONLINE)
		{
			gc_OnlineUserMap.HashMap_Add(*user);
		}
		strcpy(user->data.dst_id, user->data.src_id);
		send_data(user);
		break;
	case CMD_REGISTER:
		cout << "user register!" << endl;
		memcpy(&info, &user->data, sizeof(ts_userInfo));

		if (0 == user->user_register(db.mysql, info))
			//注册成功
			user->data.cmd = CMD_REGISTERSUCCESS;
		else
			//注册失败
			user->data.cmd = CMD_REGISTERFAILED;

		strcpy(user->data.dst_id, user->data.src_id);
		send_data(user);
		break;
	case CMD_USERDATA:

		break;
	case CMD_CLOSECHAT:

		user->data.cmd = user->user_logout(db.mysql, info);
		if ( user->data.cmd == D_USER_ONLINE )
		{
			gc_OnlineUserMap.HashMap_Del(*user);
		}
		break;
	default:
		break;
	}

}

void comm::send_data(userInfo * user)
{
	if (write(user->sock_fd, &user->data, sizeof(user->data)) < 0)
	{
		cout << "Error:send_data failed , Reason:" << strerror(errno) << endl;
	}


}




