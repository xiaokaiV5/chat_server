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
		len = read(user->sock_fd, &user->msg, sizeof(user->msg));
		if (len < 0)
		{
			printf("COMM:Read message error, errno:%d, Reason:%s \n", errno, strerror(errno));
			//myCout << "read message error!" << endl;
			break;
		}

		else if (len == 0)
		{
			cout << "COMM:User close the socket !" << endl;
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

	switch (user->msg.cmd)
	{
	case CMD_LOGIN:
		cout << "LOGIN: User login !" << endl;
		memcpy(&info, &user->msg.data, sizeof(ts_userInfo));

		user->user_login(db.mysql, info);

		if (user->msg.cmd == CMD_LOGINSUCCESS)
		{
			user->set_Account_name(user->msg.src_id);

			//Add to list of online user.
			gc_OnlineUserMap.HashMap_Add(*user);
		}
		strcpy(user->msg.dst_id, user->msg.src_id);
		send_data(user);
		usleep(500 * 1000);//wait 500 milliseconds to complete client initialization.  ===
		if (user->msg.cmd == CMD_LOGINSUCCESS)
		{
			//Boadcast to online users.
			gc_OnlineUserMap.HashMap_Travel(*user);
		}

		break;
	case CMD_REGISTER:
		cout << "REGISTER: User register!" << endl;
		memcpy(&info, &user->msg.data, sizeof(ts_userInfo));

		if (0 == user->user_register(db.mysql, info))
			user->msg.cmd = CMD_REGISTERSUCCESS;	//注册成功
		else
			user->msg.cmd = CMD_REGISTERFAILED;	//注册失败

		strcpy(user->msg.dst_id, user->msg.src_id);
		send_data(user);
		break;
	case CMD_USERDATA:
	{
		int sockFd = gc_OnlineUserMap.HashMap_getUserSockFd(user->msg.dst_id);
		
		send_data(sockFd, user->msg);
		break;

	}
	case CMD_CLOSECHAT:
		cout << "The user that name is " << user->get_Account_name() << " logout." << endl;
		user->msg.cmd = user->user_logout(db.mysql, info);

		//Del the info from online-list.
		gc_OnlineUserMap.HashMap_Del(*user);
		//Boadcast to online users.
		gc_OnlineUserMap.HashMap_Travel(*user);

		break;
	default:
		break;
	}

}

void send_data(userInfo * user)
{
	cout << "sockfd:"<<user->sock_fd << endl;
	if (write(user->sock_fd, &user->msg, sizeof(user->msg)) < 0)
	{
		cout << "Error:send_data(userInfo * user) failed , Reason:" << strerror(errno) << endl;
	}
}

void send_data(int sockFd, USER_DATA data)
{
	if (write(sockFd, reinterpret_cast<char *>(&data), sizeof(USER_DATA)) < 0)
	{
		cout << "Error:send_data(sockFd, data) failed , Reason:" << strerror(errno) << endl;
	}

	return;
}

void send_data(int sockfd, userInfo * user)
{
	cout << "sockfd:" << sockfd  << endl;
	if (write(sockfd, &user->msg, sizeof(user->msg)) < 0)
	{
		cout << "Error:send_data(sockfd, user) failed , Reason:" << strerror(errno) << endl;
	}

}




