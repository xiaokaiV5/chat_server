#include <string>
#include <string.h>
#include <unistd.h>
#include "online_user_operate.h"

using namespace std;
#define d_bucket_num	1000	//��ʼ��hashͰ������

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
	//printf("sockfd:%d, =============\n", user.sock_fd);
	//cout << "HashMap_Add ======= "<< user.get_Account_name() << " sock_fd: "<< user.sock_fd << endl;
	uMap.insert(make_pair(user.get_Account_name(), user));
	// travel .
	HashMap_Travel();
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
		//cout << "scok ===:" << iter->second.sock_fd << endl;
		cout << iter->second.get_Account_name() << iter->second.getPasswd(iter->second.get_Account_name()) << endl;
		iter++;
		//cout << "account:" << iter->first << " passwd:" << iter->second.passwd << " name:" << iter->second.name << " age:" << iter->second.age\
		//	<< " ID_Card��" << iter->second.ID_card << " phoneNum:" << iter->second.phoneNum << " time_register:" << iter->second.time_register\
		//	<< " time_login:" << iter->second.time_login << endl;
	}

	return;
}

//Temp broadcast all user, then will change to broadcast the user info of new go online .
#define d_account_len	20
void myHashMap::HashMap_Travel(userInfo newOnlineUser)
{
	cout << "Broadcast to online user what the list of all online user info." << endl;
	int i = 0;
	auto iter = uMap.begin();
	while (iter != uMap.end())
	{
		i = 0;
		sprintf(this->msg.dst_id, "%s", iter->second.get_Account_name());
		cout << "======" << iter->second.get_Account_name() << endl;
		cout << "=========11111" << this->msg.dst_id << endl;
		auto iterTmp = uMap.begin();

		while (iterTmp != uMap.end())
		{
			sprintf(this->msg.data + i * d_account_len, "%s", iterTmp->second.get_Account_name());
			i++;
			iterTmp++;
		}
		cout << "iter:" << iter->second.get_Account_name() << iter->second.sock_fd << endl;

		this->msg.cmd = CMD_Onlineuser;
		this->msg.dst_id[0] = i;//���������û��б�ʱ��һ�ֽڴ����û�������-->����bug�����ֻ�ܷ���255������������Ϊֻ�����������ߵ��û�

		//send_data(&iterTmp->second);
		write(iter->second.sock_fd, &this->msg, sizeof(USER_DATA));
		cout << "Send online user name, len :" << i * 20 + 20 << this->msg.data << endl;
		iter++;
	}
}

void myHashMap::HashMap_Clear()
{
	cout << "About to clear online user information " << endl;
	uMap.clear();
	return;
}

size_t myHashMap::HashMap_Size()
{
	cout << "uMap.cout=" << uMap.size();
	return uMap.size();
}

userInfo myHashMap::HashMap_getUser(char * account)
{
	//string key = account;

	if (strlen(account))
	{
		userInfo &tmpUser = uMap[account];
		cout << tmpUser.get_Account_name() << tmpUser.getPasswd(tmpUser.get_Account_name()) << endl;
		//return uMap[account];
	}
}
