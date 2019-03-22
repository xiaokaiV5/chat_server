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
	//添加元素到哈希链表
	int HashMap_Add(userInfo user);
	//从哈希链表删除指定元素
	int HashMap_Del(userInfo user);
	
	//遍历哈希链表
	void HashMap_Travel();
	//遍历哈希链表,通知新用户上线。
	void HashMap_Travel(userInfo newOnlineUser);
	//清楚哈希链表的所有数据
	void HashMap_Clear();
	//获取在线用户的总数量
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