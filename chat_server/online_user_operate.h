#pragma once
#ifndef __ONLINE_USER_OPERATE_H__
#define __ONLINE_USER_OPERATE_H__
#include "user.h"
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
	//�����ϣ�������������
	void HashMap_Clear();
	//��ȡ�����û���������
	size_t HashMap_Size();

protected:
private:
	HashMap uMap;
};





#endif