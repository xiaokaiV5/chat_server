#pragma once
#ifndef __USER_H__
#define __USER_H__
#include <string>
#include <thread>
#include "base_sock.h"

#include "myDB.h"

using namespace std;



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

class userInfo: public myDB, public base_sock, public baseInfo
{
public:
	userInfo();
	~userInfo();
	bool checking_account(string account);
	bool checkPasswd(string passwd);
	int user_register(ts_userInfo);
public:
	thread::id tid_work;

protected:

private:

};


#endif

