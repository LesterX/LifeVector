#ifndef DATABASE_H
#define DATABASE_H
#include<iostream>
#include<string>
#include<mysql/mysql.h> 
// If mysql.h is not installed, "sudo apt-get install libmysqlclient-dev"
// If that command didn't work, try "sudo apt-get install default-libmysqlclient-dev"
// Need to add "-lmysqlclient" when compiling
using namespace std;

class Database
{
public:
	Database();
	~Database();
	bool initDB(string host, string user, string pw, string db_name);
	bool exeSQL(string sql);
    std::string getSQLResult(string sql);
private:
	MYSQL *connection;
	MYSQL_RES *result;
	MYSQL_ROW row;
};

#endif
