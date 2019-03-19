#include "online_user_operate.h"
#include <string>

using namespace std;
#define d_bucket_num	1000	//初始化hash桶的数量

myHashMap gc_OnlineUserMap;

myHashMap::myHashMap()
{
	HashMap mapOnline(d_bucket_num);
}

myHashMap::~myHashMap()
{
	HashMap_Clear();
}

int myHashMap::HashMap_Add(userInfo user)
{
	uMap.insert(make_pair(user.get_Account_name(), user));
	return 0;
}

int myHashMap::HashMap_Del(userInfo user)
{
	cout << "Del user:" << user.get_Account_name() << endl;
	uMap.erase(user.get_Account_name());
	return 0;
}

void myHashMap::HashMap_Travel()
{
	cout << "Travel online user info" << endl;
	auto iter = uMap.begin();
	while (iter != uMap.end())
	{
		//cout << "account:" << iter->first << " passwd:" << iter->second.passwd << " name:" << iter->second.name << " age:" << iter->second.age\
		//	<< " ID_Card：" << iter->second.ID_card << " phoneNum:" << iter->second.phoneNum << " time_register:" << iter->second.time_register\
		//	<< " time_login:" << iter->second.time_login << endl;
			
	}

	return ;
}

void myHashMap::HashMap_Clear()
{
	cout << "About to clear online user information " << endl;
	uMap.clear();

	return ;
}

size_t myHashMap::HashMap_Size()
{
	cout << "uMap.cout=" << uMap.size();
	return uMap.size();
}