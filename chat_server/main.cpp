#include <cstdio>
#include <iostream>
#include <string>
#include <mysql/mysql.h>

#include "user.h"
#include "comm.h"
#include "myDB.h"
#include "define.h"
#include "online_user_operate.h"
using namespace std;

int main()
{ 
	myCout<< "The process start!!!" << endl;

	myHashMap OnlineUserMap;	//初始化在线用户hashMap

	//db.Init_DB("localhost", "root", "123456", "chatServer");
	//db.ExeSQL("SELECT * FROM account_info WHERE account=\"miaoyu\"");
	db.QueryDatabase1(db.mysql);
	//db.AccountIsExists("111");
	comm comm_server;
	if (comm_server.comm_init(LISTEN_PORT) != 0)
	{
		cout << "comm_init error , exit"<<endl;
		return -1;
	}
		
	comm_server.thread_accept();



    return 0;
}