#pragma once
#ifndef __USER_H__
#define __USER_H__
#include <string>
#include <thread>
#include "base_sock.h"

#include "myDB.h"

using namespace std;

//用户状态
enum User_state {
	D_USER_OFFLINE,
	D_USER_ONLINE,
	D_USER_BUSY,
	D_USER_Out_of_state,
};

enum Sex_type
{
	Sex_Man,
	Sex_Woman,
	Sex_TwoInOne,
	Sex_Unkonwen,
};

//注册用户的基本信息
class baseInfo
{
public:
	baseInfo();
	~baseInfo();
public:
	string get_Account_name(int id);
	string getPasswd(string accountName);
	time_t get_time_register(string accountName);
	time_t get_time_login(string accountName);
	int getAge(string accountName);
	string getName(string accountName);
	string get_ID_card(string accountName);
	string get_phoneNum(string accountName);
	string get_AllInfo(int id);
	string get_AllInfo(string accountName);
	string increase_one();
protected:

private:
	int id;
	string account_name;	//账户名
	string passwd;			//密码
	time_t time_register;	//注册时间
	time_t time_login;      //最后一次登录时间
	int age;				//年龄
	string name;			//名字
	string ID_card;			//身份证信息
	string phoneNum;		//电话号码
};

class userInfo: public myDB, public base_sock, public baseInfo
{
public:
	userInfo();
	~userInfo();
	bool checking_account(string account);
	bool checkPasswd(string passwd);
	int user_register(MYSQL* mysqlDB, ts_userInfo info);
	int user_login(MYSQL* mysqlDB, ts_userInfo info);
	int user_logout(MYSQL* mysqlDB, ts_userInfo info);
public:
	thread::id tid_work;
	USER_DATA data;
	int onlineState;	//在线状态:离线，在线，忙碌，离开。
protected:
	
private:
	
};


#endif

