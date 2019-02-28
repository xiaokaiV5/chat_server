#pragma once
#ifndef __MYDB_H__
#define __MYDB_H__

#include <string>
#include <iostream>
#include <mysql/mysql.h>

using namespace std;

#define d_sqlcmd_len	256//sql��䳤��
#define DB_TABLE	"account_info"

#define USERIDSIZE      20
#define USERDATASIZE    1000
#define MAXUSER         100
#define CMDSIZE         1
/* �����������͵����� */
#define CMD_LOGIN           1
#define CMD_REGISTER        2
#define CMD_USERDATA        10
#define CMD_CLOSECHAT       12

/* ���������ص����� */
#define CMD_LOGINSUCCESS    3
#define CMD_REGISTERSUCCESS 4
#define CMD_LOGINFAILED     5
#define CMD_REGISTERFAILED  6
#define CMD_REGISTEREXISTS  7
#define CMD_GetOnlineuser   8
#define CMD_Onlineuser      9
#define CMD_REPEATLOGIN     11

#define DATASIZE        CMDSIZE + USERIDSIZE*2 + USERDATASIZE

#define		D_ACCOUNT_INVALID		-1	//account is invalid.
#define		D_PASSWD_ERROR			-2	//passwd error
#define		D_DB_ERROR				-3	//datebase error or command execute failed.
#define		D_PASSWD_CURRECT		0	//passwd is currect.


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
	myDB(MYSQL* mysqlDB);
	~myDB();
	bool ConnectDatabase(MYSQL* mysqlDB, string host, string user, string pwd, string dbname);
	bool QueryDatabase1(MYSQL* mysqlDB);
	void FreeConnect(MYSQL* mysqlDB);
	bool QueryDatabase2(MYSQL* mysqlDB);
	//bool Init_DB(string host, string user, string pwd, string dbname);
	bool InsertData(MYSQL* mysqlDB, ts_userInfo info);
	bool AccountIsExists(MYSQL* mysqlDB, char *account);
	int CheckPasswd(MYSQL* mysqlDB, char *account, char *passwd);
public:
	char query[d_sqlcmd_len];
	MYSQL* mysql;		//����mysql���ָ��

protected:
	
private:
	MYSQL_ROW row;		//���з��صĲ�ѯ��Ϣ
	MYSQL_RES* result;	//ָ���ѯ�����ָ��
	//MYSQL_FIELD* field;

	MYSQL_FIELD *filled;  //�ֶ�������
	char field[32][32];  //���ֶ�����ά����
};

extern myDB db;


#endif