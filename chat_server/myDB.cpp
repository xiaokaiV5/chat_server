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

//�������ݿ�
bool myDB::ConnectDatabase(MYSQL* mysqlDB, string host, string user, string pwd, string dbname)
{
	//��ʼ��mysqlDB
	mysql_init(mysqlDB);  //����mysqlDB�����ݿ�

	//����false������ʧ�ܣ�����true�����ӳɹ�
	if (!(mysql_real_connect(mysqlDB, host.c_str(), user.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ
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
//�ѷ���
//bool myDB::ExeSQL(MYSQL* mysqlDB, string sql)
//{
//	/*ִ��ʧ��*/
//	if (mysql_query(mysql, sql.c_str()))
//	{
//		myCout << "query fail: " << mysql_error(mysql);
//		exit(1);
//	}
//	else
//	{
//		/*��ȡ�����*/
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


//��ʵ���е����ݿ����������д��sql��䣬Ȼ����mysql_query(mysql,query)����ɣ������������ݿ�����ɾ�Ĳ�
//��ѯ����
bool myDB::QueryDatabase1(MYSQL* mysqlDB)
{
	sprintf(query, "select * from %s", DB_TABLE); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����
	
	mysql_query(mysqlDB, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������
	//����0 ��ѯ�ɹ�������1��ѯʧ��
	if (mysql_query(mysqlDB, query))        //ִ��SQL���
	{
		printf("Query failed (%s)\n", mysql_error(mysqlDB));
		return false;
	}
	else
	{
		printf("query success\n");
	}

	//��ȡ�����
	if (!(result = mysql_store_result(mysqlDB)))    //���sql�������󷵻صĽ����
	{
		printf("Couldn't get result from %s\n", mysql_error(mysqlDB));
		return false;
	}

	int fieldnum = mysql_num_fields(result);
	myCout << fieldnum << endl;


	//��ӡ��������
	printf("number of dataline returned: %d\n", mysql_affected_rows(mysqlDB));

	//һ��һ�д�ӡ
	while (row = mysql_fetch_row(result))//while row!=NULL
	{
		for (int j = 0; j < fieldnum; j++)
		{
			//һ��һ�д�ӡ
			myCout << row[j] << "\t\t";
		}
		myCout << endl;
	}

	mysql_free_result(result);
	return true;
}

bool myDB::QueryDatabase2(MYSQL* mysqlDB)
{
	memset(query, 0, sizeof(query));
	sprintf(query, "select * from %s", DB_TABLE);
	mysql_query(mysqlDB, "set names gbk");
	//����0 ��ѯ�ɹ�������1��ѯʧ��
	if (mysql_query(mysqlDB, query))        //ִ��SQL���
	{
		printf("Query failed (%s)\n", mysql_error(mysqlDB));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	result = mysql_store_result(mysqlDB);
	//��ӡ��������
	printf("number of dataline returned: %d\n", mysql_affected_rows(mysqlDB));
	for (int i = 0; filled = mysql_fetch_field(result); i++)  //��ȡ�ֶ���
		strcpy(field[i], filled->name);
	int j = mysql_num_fields(result);  // ��ȡ����
	for (int i = 0; i < j; i++)  //��ӡ�ֶ�
		printf("%10s\t", field[i]);
	printf("\n");
	while (row = mysql_fetch_row(result))
	{
		for (int i = 0; i < j; i++)
			printf("%10s\t", row[i]);
		printf("\n");
	}

	mysql_free_result(result);
	return true;
}

//�ͷ���Դ
void myDB::FreeConnect(MYSQL* mysqlDB)
{
	//�ͷ���Դ
	mysql_free_result(result);
	mysql_close(mysqlDB);
}
/***************************���ݿ����***********************************/


bool myDB::InsertData(MYSQL* mysqlDB, ts_userInfo info)
{
	sprintf(query, "insert into %s (account , passwd) value (\"%s\", \"%s\");", DB_TABLE, info.account, info.passwd);
	cout << query;
	if (mysql_query(mysqlDB, query))        //ִ��SQL���
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

//�����˻��Ƿ����
bool myDB::AccountIsExists(MYSQL* mysqlDB, char * account)
{
	sprintf(query, "select * from %s where account=\'%s\'", DB_TABLE, account); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����
	cout << query<<endl;
	mysql_query(mysqlDB, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������
	//����0 ��ѯ�ɹ�������1��ѯʧ��
	if (mysql_query(mysqlDB, query))        //ִ��SQL���
	{
		printf("Query failed (%s)\n", mysql_error(mysqlDB));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	//��ȡ�����
	if (!(result = mysql_store_result(mysqlDB)))    //���sql�������󷵻صĽ����
	{
		printf("Couldn't get result from %s\n", mysql_error(mysqlDB));
		return false;
	}

	//��ӡ��������
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
}

int myDB::CheckPasswd(MYSQL * mysqlDB, char * account, char * passwd)
{
	int ret = D_DB_ERROR;
	sprintf(query, "select account,passwd from %s where account='%s'", DB_TABLE, account);
	if ( mysql_query(mysqlDB, query) )
	{
		cout << "Query failed, Reason:" << mysql_error(mysqlDB);
		ret = D_DB_ERROR;
	}
	else
	{
		result = mysql_store_result(mysqlDB);
		if (result)
		{
			int columns = mysql_num_fields(result);
			row = mysql_fetch_row(result);
			if (columns == 2)
			{
				if (0 == strncmp(passwd, row[columns - 1], max(strlen(passwd), strlen(row[columns - 1]))))
				{
					ret = D_PASSWD_CURRECT;
					cout << "Passwd correct." << endl;
				}
				else
				{
					ret = D_PASSWD_ERROR;
					cout << "Passwd error." << endl;
				}
			} 
			else
			{
				cout << "CheckPasswd error." << endl;
				ret = D_DB_ERROR;
			}
		} 
		else
		{
			cout << "Couldn't get result from " << DB_TABLE << " Reason: " << mysql_error(mysqlDB);
			ret = D_DB_ERROR;
		}
	}

	return ret;
}




