#include <cstdio>
#include <iostream>
#include <string>
#include <mysql/mysql.h>

#include "user.h"
#include "comm.h"
#include "myDB.h"

using namespace std;

int main()
{
	cout << "The process start!!!" << endl;

	comm comm_server;

	myDB db;
	db.Init_DB("127.0.0.1", "root", "123456", "chatServer");
	db.ExeSQL("SELECT * from account_info");

    return 0;
}