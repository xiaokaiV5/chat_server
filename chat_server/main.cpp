#include <cstdio>
#include <iostream>
#include <string>
#include <mysql/mysql.h>

#include "user.h"
#include "comm.h"
#include "myDB.h"
#include "define.h"
using namespace std;

int main()
{
	myCout<< "The process start!!!" << endl;

	myDB db;
	db.Init_DB("localhost", "root", "123456", "chatServer");
	db.ExeSQL("SELECT * FROM account_info WHERE account=\"miaoyu\"");

	comm comm_server;
	comm_server.comm_init(5005);
	comm_server.thread_accept();



    return 0;
}