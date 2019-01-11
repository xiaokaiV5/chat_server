#pragma once
#ifndef __USER_H__
#define __USER_H__
#include <string>
#include <thread>
#include "base_sock.h"

using namespace std;

enum Sex_type
{
	Sex_Man,
	Sex_Woman,
	Sex_TwoInOne,
	Sex_Unkonwen,
};

class userInfo:public base_sock
{
public:
	userInfo();
	~userInfo();
	bool checkPasswd(string passwd);
	void logout();

public:
	thread::id tid_work;
protected:
	int id;
	string passwd;
	int logTime;

private:
	int age;
	string name;
	string ID_card;
	string phoneNum;
};


#endif

