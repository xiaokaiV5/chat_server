#pragma once
#ifndef __MYDB_H__
#define __MYDB_H__

#include <string>
#include <iostream>
#include <mysql/mysql.h>

using namespace std;


#define d_sqlcmd_len	256//sql语句长度
#define DB	"account_info"

#define USERIDSIZE      20
#define USERDATASIZE    1000
#define MAXUSER         100
#define CMDSIZE         1
/* 给服务器发送的命令 */
#define CMD_LOGIN           1
#define CMD_REGISTER        2
#define CMD_USERDATA        10
#define CMD_CLOSECHAT       12

/* 服务器返回的命令 */
#define CMD_LOGINSUCCESS    3
#define CMD_REGISTERSUCCESS 4
#define CMD_LOGINFAILED     5
#define CMD_REGISTERFAILED  6
#define CMD_REGISTEREXISTS  7
#define CMD_GetOnlineuser   8
#define CMD_Onlineuser      9
#define CMD_REPEATLOGIN     11

#define DATASIZE        CMDSIZE + USERIDSIZE*2 + USERDATASIZE

typedef struct user_data
{
	unsigned char cmd;
	char dst_id[USERIDSIZE];
	char src_id[USERIDSIZE];
	char data[USERDATASIZE];
}USER_DATA;


#define ACT_LEN		64
#define PWD_LEN		64
#define NAME_SIZE	64
#define	ID_CARD_LEN	19
#define PHONE_NUM_LEN	32

typedef struct user_info_st
{
	char account[ACT_LEN];
	char passwd[PWD_LEN];
	int  age;
	char name[NAME_SIZE];
	char idCard[ID_CARD_LEN];
	char phoneNum[PHONE_NUM_LEN];
}ts_userInfo;


class myDB
{
public:
	myDB();
	~myDB();
	bool ConnectDatabase(string host, string user, string pwd, string dbname);
	bool QueryDatabase1();
	//bool Init_DB(string host, string user, string pwd, string dbname);
	bool ExeSQL(string sql);	//Online examples
	bool InsertData(ts_userInfo info);
	bool AccountIsExists(char *account);
public:
	char query[d_sqlcmd_len];
protected:
	
private:
	MYSQL* mysql;		//连接mysql句柄指针
	MYSQL_ROW row;		//按行返回的查询信息
	MYSQL_RES* result;	//指向查询结果的指针
	MYSQL_FIELD* field;
};
#endif