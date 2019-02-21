#include <iostream>
#include <string>
#include <string.h>
#include "comm.h"
#include "user.h"
#include "myDB.h"
#include "define.h"
userInfo::userInfo()
{

}

userInfo::~userInfo()
{
	//myCout << "user " << " " << "delete himself!!!" << endl;
}

bool userInfo::checking_account(string account)
{
	string account_stored = this->get_Account_name(2);

	myCout << "account : " << account << endl;
	return false;
}

bool userInfo::checkPasswd(string passwd)
{
	bool ret = false;
	string passwd_Stored = this->getPasswd("123456");

	//if (passwd == this->posswd)// correct
	if(passwd.c_str() == passwd_Stored.c_str())
	{
		myCout << "The passwd is correct! " << endl;
		ret = true;
	}
	else
	{
		myCout << "Passwd error! " << endl;
		ret = false;
	}
	return ret;
}

int userInfo::user_register(ts_userInfo info)
{
	int ret = 0;
	cout << "Register: account: " << info.account << " passwd: " << info.passwd << endl;

	bool act_exist = false;
	//检查此用户名在数据库是否已经存在。
	if (AccountIsExists(info.account))
	{
		cout << "Account " << info.account << " already exits, register failed!" << endl;
	} 
	else
	{
		//添加到数据库
		//return static_cast<int>(InsertData(info));
		//添加到数据库。
		if (true == InsertData(info))
		{
			cout << "Insert user to database success!" << endl;
			ret = 0;
		}
		else
		{
			cout << "Insert user to database faie!" << endl;
			ret = -1;
		}
	}

	return ret;
}


baseInfo::baseInfo()
{
}

baseInfo::~baseInfo()
{
}

string baseInfo::get_Account_name(int id)
{
	return string();
}
string baseInfo::getPasswd(string accountName)
{
	string passwd;

	//myDB::ExeSQL();
	return passwd;
}

time_t baseInfo::get_time_register(string accountName)
{
	return time_t();
}

time_t baseInfo::get_time_login(string accountName)
{
	return time_t();
}

int baseInfo::getAge(string accountName)
{
	return 0;
}

string baseInfo::getName(string accountName)
{
	return string();
}

string baseInfo::get_ID_card(string accountName)
{
	return string();
}

string baseInfo::get_phoneNum(string accountName)
{
	return string();
}

string baseInfo::get_AllInfo(int id)
{
	return string();
}
string baseInfo::get_AllInfo(string accountName)
{
	return string();
}

string baseInfo::increase_one()
{
	return string();
}

