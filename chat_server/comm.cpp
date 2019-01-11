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
	//int server_sockfd;//���������׽���
	struct sockaddr_in my_addr;   //�����������ַ�ṹ��

	memset(&my_addr, 0, sizeof(my_addr)); //���ݳ�ʼ��--����
	my_addr.sin_family = AF_INET; //����ΪIPͨ��
	my_addr.sin_addr.s_addr = INADDR_ANY;//������IP��ַ--�������ӵ����б��ص�ַ��
	my_addr.sin_port = htons(LISTEN_PORT); //�������˿ں�

	/*�������������׽���--IPv4Э�飬��������ͨ�ţ�TCPЭ��*/
	this->socket_AsS = socket(PF_INET, SOCK_STREAM, 0);
	if (this->socket_AsS < 0)
	{
		perror("socket error");
		return 1;
	}
	//

	/*���׽��ְ󶨵��������������ַ��*/
	if (bind(this->socket_AsS, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("bind error");
		return 1;
	}

	/*������������--�������г���Ϊ5*/
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
	struct sockaddr_in remote_addr; //�ͻ��������ַ�ṹ��
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
			//�����̻߳���̶Դ��û�����������Ϣ�ȼ�⣡����
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

	//��д���պ��������˺ź�������sqlite���ݿ��е����ݽ��бȶ���֤����֤ͨ���������Ȩ��


	return NULL;
}
