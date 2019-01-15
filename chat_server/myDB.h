#pragma once
#ifndef __MYDB_H__
#define __MYDB_H__
#include <string>
#include <iostream>
#include <mysql/mysql.h>



using namespace std;

class myDB
{
public:
	myDB();
	~myDB();
	bool Init_DB(string host, string user, string pwd, string dbname);
	bool ExeSQL(string sql);	//Online examples
protected:
	
private:
	MYSQL* mysql;		//连接mysql句柄指针
	MYSQL_ROW row;		//按行返回的查询信息
	MYSQL_RES* result;	//指向查询结果的指针
	MYSQL_FIELD* field;
};
#endif