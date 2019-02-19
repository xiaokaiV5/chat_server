#pragma once
#ifndef __USER_H__
#define __USER_H__
#include <string>
#include <thread>
#include "base_sock.h"
#include "myDB.h"

using namespace std;

#define USERIDSIZE      20
#define USERDATASIZE    1000
#define MAXUSER         100
#define CMDSIZE         1
/* 给服务器发送的命令 */
#define CMD_LOGIN           1
#define CMD_REGISTER        2
#define CMD_USERDATA        10
#define CMD_CLOSECHAT       12

/* 服务器返回的命令 */
#define CMD_LOGINSUCCESS    3
#define CMD_REGISTERSUCCESS 4
#define CMD_LOGINFAILED     5
#define CMD_REGISTERFAILED  6
#define CMD_REGISTEREXISTS  7
#define CMD_GetOnlineuser   8
#define CMD_Onlineuser      9
#define CMD_REPEATLOGIN     11

#define DATASIZE        CMDSIZE + USERIDSIZE*2 + USERDATASIZE

typedef struct user_data
{
	unsigned char cmd;
	char dst_id[USERIDSIZE];
	char src_id[USERIDSIZE];
	char data[USERDATASIZE];
}USER_DATA;


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

class userInfo: public myDB,public base_sock, private baseInfo
{
public:
	userInfo();
	~userInfo();
	bool checking_account(string account);
	bool checkPasswd(string passwd);

public:
	thread::id tid_work;

protected:

private:

};


#endif

