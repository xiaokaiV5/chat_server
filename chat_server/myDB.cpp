#include <mysql/mysql.h>

#include "myDB.h"
#include "define.h"
myDB::myDB()
{
	mysql = mysql_init(NULL);
	if (mysql == NULL)
	{
		myCout << "MYSQL Error: " << mysql_error(mysql);
		exit(-1);
	}
}

myDB::~myDB()
{ 
	if (!mysql)
	{
		mysql_close(mysql);
	}
}

 bool myDB::Init_DB(string host, string user, string pwd, string dbname)
{
	/*连接数据库*/
	if (!mysql_real_connect(mysql, host.c_str(), user.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0))
	{
		myCout << "connect fial: " << mysql_error(mysql);
		exit(-1);
	}
	myCout << "mysql connect success!" << endl;
	return true;
}

bool myDB::ExeSQL(string sql)
{
	 /*执行失败*/
	if (mysql_query(mysql, sql.c_str()))
	{
		myCout << "query fail: " << mysql_error(mysql);
		exit(1);
	}
	else
	{
		/*获取结果集*/
		result = mysql_store_result(mysql);

		int fieldnum = mysql_num_fields(result);
		myCout << fieldnum << endl;

		while (row = mysql_fetch_row(result))//while row!=NOLL
		{
			for (int j = 0; j < fieldnum; j++)
			{
				myCout << row[j] << "\t\t";
			}
			myCout << endl;
		}
		//for (int i = 0; i < 6; i++)
		//{
		//	row = mysql_fetch_row(result);
		//	if (row <= 0)
		//		break;
		//	for (int j = 0; j < fieldnum; j++)
		//	{
		//		myCout << row[j] << "\t\t";
		//	}
		//	myCout << endl;
		//}
		mysql_free_result(result);
	}
	return true;
}

