#include <mysql/mysql.h>
#include <string.h>
#include "myDB.h"
#include "define.h"

myDB db;

myDB::myDB(MYSQL* mysqlDB)
{
	mysqlDB = mysql_init(NULL);
	if (mysqlDB == NULL)
	{
		myCout << "MYSQL Error: " << mysql_error(mysqlDB);
		exit(-1);
	}
	else
	{
		ConnectDatabase(mysqlDB, "localhost", "root", "123456", "chatServer");
	}
}

myDB::myDB()
{
	mysql = mysql_init(NULL);
	if (mysql == NULL)
	{
		myCout << "MYSQL Error: " << mysql_error(mysql);
		exit(-1);
	}
	else
	{
		ConnectDatabase(mysql, "localhost", "root", "123456", "chatServer");
	}
}


myDB::~myDB()
{ 
	cout << "~myDB()" << endl;
}

//连接数据库
bool myDB::ConnectDatabase(MYSQL* mysqlDB, string host, string user, string pwd, string dbname)
{
	//初始化mysqlDB
	mysql_init(mysqlDB);  //连接mysqlDB，数据库

	//返回false则连接失败，返回true则连接成功
	if (!(mysql_real_connect(mysqlDB, host.c_str(), user.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去
	{
		myCout << "connect fial: " << mysql_error(mysqlDB);
		return false;
	}
	else
	{
		myCout << "mysqlDB connect success!" << endl;
		return true;
	}
}
//已废弃
//bool myDB::ExeSQL(MYSQL* mysqlDB, string sql)
//{
//	/*执行失败*/
//	if (mysql_query(mysql, sql.c_str()))
//	{
//		myCout << "query fail: " << mysql_error(mysql);
//		exit(1);
//	}
//	else
//	{
//		/*获取结果集*/
//		result = mysql_store_result(mysql);
//
//		int fieldnum = mysql_num_fields(result);
//		myCout << fieldnum << endl;
//
//		while (row = mysql_fetch_row(result))//while row!=NOLL
//		{
//			for (int j = 0; j < fieldnum; j++)
//			{
//				myCout << row[j] << "\t\t";
//			}
//			myCout << endl;
//		}
//		//for (int i = 0; i < 6; i++)
//		//{
//		//	row = mysql_fetch_row(result);
//		//	if (row <= 0)
//		//		break;
//		//	for (int j = 0; j < fieldnum; j++)
//		//	{
//		//		myCout << row[j] << "\t\t";
//		//	}
//		//	myCout << endl;
//		//}
//		mysql_free_result(result);
//	}
//	return true;
//}


//其实所有的数据库操作都是先写个sql语句，然后用mysql_query(mysql,query)来完成，包括创建数据库或表，增删改查
//查询数据
bool myDB::QueryDatabase1(MYSQL* mysqlDB)
{
	sprintf(query, "select * from %s", DB_TABLE); //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以
	mysql_query(mysqlDB, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
	//返回0 查询成功，返回1查询失败
	if (mysql_query(mysqlDB, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n", mysql_error(mysqlDB));
		return false;
	}
	else
	{
		printf("query success\n");
	}

	/*获取结果集*/
	result = mysql_store_result(mysql);

	int fieldnum = mysql_num_fields(result);
	myCout << fieldnum << endl;

	//获取结果集
	if (!(result = mysql_store_result(mysqlDB)))    //获得sql语句结束后返回的结果集
	{
		printf("Couldn't get result from %s\n", mysql_error(mysqlDB));
		return false;
	}

	//打印数据行数
	printf("number of dataline returned: %d\n", mysql_affected_rows(mysqlDB));

	//一行一行打印
	while (row = mysql_fetch_row(result))//while row!=NULL
	{
		for (int j = 0; j < fieldnum; j++)
		{
			//一列一列打印
			myCout << row[j] << "\t\t";
		}
		myCout << endl;
	}

	return true;
}

bool myDB::QueryDatabase2(MYSQL* mysqlDB)
{
	memset(query, 0, sizeof(query));
	sprintf(query, "select * from %s", DB_TABLE);
	mysql_query(mysqlDB, "set names gbk");
	//返回0 查询成功，返回1查询失败
	if (mysql_query(mysqlDB, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n", mysql_error(mysqlDB));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	result = mysql_store_result(mysqlDB);
	//打印数据行数
	printf("number of dataline returned: %d\n", mysql_affected_rows(mysqlDB));
	for (int i = 0; filled = mysql_fetch_field(result); i++)  //获取字段名
		strcpy(field[i], filled->name);
	int j = mysql_num_fields(result);  // 获取列数
	for (int i = 0; i < j; i++)  //打印字段
		printf("%10s\t", field[i]);
	printf("\n");
	while (row = mysql_fetch_row(result))
	{
		for (int i = 0; i < j; i++)
			printf("%10s\t", row[i]);
		printf("\n");
	}
	return true;
}

//释放资源
void myDB::FreeConnect(MYSQL* mysqlDB)
{
	//释放资源
	mysql_free_result(result);
	mysql_close(mysqlDB);
}
/***************************数据库操作***********************************/


bool myDB::InsertData(MYSQL* mysqlDB, ts_userInfo info)
{
	sprintf(query, "insert into %s (account , passwd) value (\"%s\", \"%s\");", DB_TABLE, info.account, info.passwd);
	cout << query;
	if (mysql_query(mysqlDB, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n", mysql_error(mysqlDB));
		return false;
	}
	else
	{
		printf("Insert success\n");
		return true;
	}
	return false;
}
//检测该账户是否存在
bool myDB::AccountIsExists(MYSQL* mysqlDB, char * account)
{
	sprintf(query, "select * from %s where account=\'%s\'", DB_TABLE, account); //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以
	cout << query<<endl;
	mysql_query(mysqlDB, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
	//返回0 查询成功，返回1查询失败
	if (mysql_query(mysqlDB, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n", mysql_error(mysqlDB));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	//获取结果集
	if (!(result = mysql_store_result(mysqlDB)))    //获得sql语句结束后返回的结果集
	{
		printf("Couldn't get result from %s\n", mysql_error(mysqlDB));
		return false;
	}

	//打印数据行数
	printf("number of dataline returned: %d\n", mysql_affected_rows(mysqlDB));
	int lineNum = mysql_num_rows(result);
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

	return lineNum > 0 ? true : false;

	//int dataline = 0;
	//memset(query, 0, sizeof(query));
	//sprintf(query, "select * from %s WHERE account=\'%s\';", DB, account);
	//cout << query << endl;
	//if (mysql_query(mysql, query))        //执行SQL语句
	//{
	//	printf("Query failed (%s)\n", mysql_error(mysql));
	//	return false;
	//}
	//else
	//{
	//	printf("query success\n");
	//	//获取结果集
	//	if (!(result = mysql_store_result(mysql)))    //获得sql语句结束后返回的结果集
	//	{
	//		printf("Couldn't get result from %s\n", mysql_error(mysql));
	//		return false;
	//	}
	//	//打印数据行数
	//	dataline = mysql_affected_rows(mysql);
	//	printf("number of dataline returned: %d\n", dataline);
	//}

	//return (dataline>0)?true:false;
}




