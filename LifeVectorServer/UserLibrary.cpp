#include <iostream>
#include "UserLibrary.h"

UserLibrary::UserLibrary()
{
	connection = mysql_init(NULL);
	if (connection == NULL)
	{
		cout << "Connection Failed: " << mysql_error(connection);
		exit(1);
	}
}

UserLibrary::~UserLibrary()
{
	if (connection != NULL)
	{
		mysql_close(connection);
	}
}

bool UserLibrary::createUserInDB()
{

}