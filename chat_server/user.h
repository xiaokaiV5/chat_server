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
/* �����������͵����� */
#define CMD_LOGIN           1
#define CMD_REGISTER        2
#define CMD_USERDATA        10
#define CMD_CLOSECHAT       12

/* ���������ص����� */
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

//ע���û��Ļ�����Ϣ
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
	string account_name;	//�˻���
	string passwd;			//����
	time_t time_register;	//ע��ʱ��
	time_t time_login;      //���һ�ε�¼ʱ��
	int age;				//����
	string name;			//����
	string ID_card;			//���֤��Ϣ
	string phoneNum;		//�绰����
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

