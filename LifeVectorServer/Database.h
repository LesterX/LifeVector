#ifndef DATABASE_H
#define DATABASE_H
#include<iostream>
#include<string>
#include<mysql/mysql.h>
using namespace std;

class Database
{
public:
	Database();
	~Database();
	bool initDB(string host, string user, string pw, string db_name);
	bool exeSQL(string sql);
private:
	MYSQL *connection;
	MYSQL_RES *result;
	MYSQL_ROW row;
};

#endif