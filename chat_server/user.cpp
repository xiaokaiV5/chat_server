#include "user.h"

#include <iostream>
#include <string>

userInfo::userInfo()
{

}

userInfo::~userInfo()
{
	//cout << "user " << " " << "delete himself!!!" << endl;
}

bool userInfo::checkPasswd(string passwd)
{
	bool ret = false;
	//if (passwd == this->posswd)// correct
	if(passwd.c_str() == this->passwd.c_str())
	{
		cout << "The passwd is correct! " << endl;
		ret = true;
	} 
	else
	{
		cout << "Passwd error! " << endl;
		ret = false;
	}
	return ret;
}

void userInfo::logout()
{
	cout << this->name << "logout!" << endl;
	return ;
}