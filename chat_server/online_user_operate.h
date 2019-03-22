#pragma once
#ifndef __ONLINE_USER_OPERATE_H__
#define __ONLINE_USER_OPERATE_H__
#include "user.h"
#include "comm.h"
#include <unordered_map>

typedef unordered_map<string, userInfo> HashMap;
class myHashMap :public userInfo
{
public:
	myHashMap();
	~myHashMap();
	//���Ԫ�ص���ϣ����
	int HashMap_Add(userInfo user);
	//�ӹ�ϣ����ɾ��ָ��Ԫ��
	int HashMap_Del(userInfo user);
	
	//������ϣ����
	void HashMap_Travel();
	//������ϣ����,֪ͨ���û����ߡ�
	void HashMap_Travel(userInfo newOnlineUser);
	//�����ϣ�������������
	void HashMap_Clear();
	//��ȡ�����û���������
	size_t HashMap_Size();
	//Get info of online user by account 
	userInfo HashMap_getUser(char *account);

	friend void send_data(userInfo *user);
	friend void send_data(int sockfd, userInfo * user);

protected:
private:
	HashMap uMap;
};


extern myHashMap gc_OnlineUserMap;


#endif