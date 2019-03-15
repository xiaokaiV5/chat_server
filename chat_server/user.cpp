#include <iostream>
#include <string>
#include <string.h>
#include "comm.h"
#include "user.h"
#include "myDB.h"
#include "define.h"
#include "online_user_operate.h"


userInfo::userInfo() :myDB::myDB(), base_sock::base_sock(), baseInfo::baseInfo()
{
	onlineState = D_USER_OFFLINE;
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

int userInfo::user_register(MYSQL* mysqlDB, ts_userInfo info)
{
	int ret = 0;
	cout << "Register: account: " << info.account << " passwd: " << info.passwd << endl;

	bool act_exist = false;
	//检查此用户名在数据库是否已经存在。
	if (AccountIsExists(mysqlDB, info.account))
	{
		cout << "Account " << info.account << " already exits, register failed!" << endl;
	} 
	else
	{
		//添加到数据库
		//return static_cast<int>(InsertData(info));
		//添加到数据库。
		if (true == InsertData(db.mysql, info))
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

int userInfo::user_login(MYSQL * mysqlDB, ts_userInfo info)
{
	cout << "login: account:" << info.account << " passwd:" << info.passwd << endl;

	int log_resilt = CheckPasswd(mysqlDB, info.account, info.passwd);
	if ( log_resilt ==0)
	{

		onlineState = D_USER_ONLINE;
		cout << "CheckPasswd successful." << endl;
	}
	else
	{
		onlineState = D_USER_OFFLINE;
		cout << "CheckPasswd failed." << endl;
	}

	return log_resilt;
}

int userInfo::user_logout(MYSQL * mysqlDB, ts_userInfo info)
{

	return 0;
}


baseInfo::baseInfo()
{
}

baseInfo::~baseInfo()
{
}

//函数设计：根据id从整个数据库查到用户名
string baseInfo::get_Account_name(int id)
{
	return string();
}
//返回此用户的用户名
string baseInfo::get_Account_name()
{
	return this->account_name;
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

