#include <mysql/mysql.h>
#include <string.h>
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

//�������ݿ�
bool myDB::ConnectDatabase(string host, string user, string pwd, string dbname)
{
	//��ʼ��mysql
	mysql_init(mysql);  //����mysql�����ݿ�

	//����false������ʧ�ܣ�����true�����ӳɹ�
	if (!(mysql_real_connect(mysql, host.c_str(), user.c_str(), pwd.c_str(), dbname.c_str(), 0, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ
	{
		myCout << "connect fial: " << mysql_error(mysql);
		return false;
	}
	else
	{
		myCout << "mysql connect success!" << endl;
		return true;
	}
}

//��ʵ���е����ݿ����������д��sql��䣬Ȼ����mysql_query(&mysql,query)����ɣ������������ݿ�����ɾ�Ĳ�
//��ѯ����
bool myDB::QueryDatabase1()
{
	sprintf(query, "select * from %s", DB); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����
	mysql_query(mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������
	//����0 ��ѯ�ɹ�������1��ѯʧ��
	if (mysql_query(mysql, query))        //ִ��SQL���
	{
		printf("Query failed (%s)\n", mysql_error(mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	//��ȡ�����
	if (!(result = mysql_store_result(mysql)))    //���sql�������󷵻صĽ����
	{
		printf("Couldn't get result from %s\n", mysql_error(mysql));
		return false;
	}

	//��ӡ��������
	printf("number of dataline returned: %d\n", mysql_affected_rows(mysql));

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

	////��ȡ�ֶε���Ϣ
	//char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ
	//for (int i = 0; i < 4; i++)   //����֪�ֶ�����������»�ȡ�ֶ���
	//{
	//	str_field[i] = mysql_fetch_field(result)->name;
	//}
	//for (int i = 0; i < 4; i++)   //��ӡ�ֶ�
	//	printf("%10s\t", str_field[i]);
	//printf("\n");
	////��ӡ��ȡ������
	//while (row = mysql_fetch_row(result))   //����֪�ֶ���������£���ȡ����ӡ��һ��
	//{
	//	printf("%10s\t%10s\t%10s\t%10s\n", row[0], row[1], row[2], row[3]);  //row��������
	//}
	return true;
}

bool myDB::ExeSQL(string sql)
{
	 /*ִ��ʧ��*/
	if (mysql_query(mysql, sql.c_str()))
	{
		myCout << "query fail: " << mysql_error(mysql);
		exit(1);
	}
	else
	{
		/*��ȡ�����*/
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

bool myDB::InsertData(ts_userInfo info)
{
	sprintf(query, "insert into %s (account , passwd) value (\"%s\", \"%s\");", DB, info.account, info.passwd);
	cout << query;
	if (mysql_query(mysql, query))        //ִ��SQL���
	{
		printf("Query failed (%s)\n", mysql_error(mysql));
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
bool myDB::AccountIsExists(char * account)
{
	int dataline = 0;
	memset(query, 0, sizeof(query));
	sprintf(query, "select * from %s WHERE account=\'%s\';", DB, account);
	cout << query;
	if (mysql_query(mysql, query))        //ִ��SQL���
	{
		printf("Query failed (%s)\n", mysql_error(mysql));
		return false;
	}
	else
	{
		printf("query success\n");
		//��ȡ�����
		if (!(result = mysql_store_result(mysql)))    //���sql�������󷵻صĽ����
		{
			printf("Couldn't get result from %s\n", mysql_error(mysql));
			return false;
		}
		//��ӡ��������
		dataline = mysql_affected_rows(mysql);
		printf("number of dataline returned: %d\n", dataline);
	}

	return (dataline>0)?true:false;
}




