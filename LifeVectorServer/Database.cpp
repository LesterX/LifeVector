#include<iostream>
#include<cstdlib>
#include "Database.h"
using namespace std;

Database::Database()
{
	connection = mysql_init(NULL); 
	if (connection == NULL)
	{
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
}

Database::~Database()
{
	if (connection != NULL) 
	{
		mysql_close(connection);
	}
}

bool Database::initDB(string host, string user, string pwd, string db_name)
{
	// Build a connection with database
	connection = mysql_real_connect(connection, host.c_str(),
		user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
	if (connection == NULL)
	{
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
	return true;
}

bool Database::exeSQL(string sql)
{
	if (mysql_query(connection, sql.c_str()))
	{
		cout << "Query Error:" << mysql_error(connection);
		exit(1);
	}
	else
	{
		result = mysql_use_result(connection); // Get Result
		// mysql_field_count() return number of columns
		for (int i = 0; i < mysql_field_count(connection); ++i)
		{
			// Get next row
			row = mysql_fetch_row(result);
			if (row <= 0)
				break;
			// mysql_num_fields return number of words
			for (int j = 0; j < mysql_num_fields(result); ++j)
			{
				cout << row[j] << " ";
			}
			cout << endl;
		}
		// Free memory
		mysql_free_result(result);
	}
	return true;
}