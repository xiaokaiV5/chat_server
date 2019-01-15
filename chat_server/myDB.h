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
	MYSQL* mysql;		//����mysql���ָ��
	MYSQL_ROW row;		//���з��صĲ�ѯ��Ϣ
	MYSQL_RES* result;	//ָ���ѯ�����ָ��
	MYSQL_FIELD* field;
};
#endif