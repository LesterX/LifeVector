1. 	Make sure you have mysql installed

2.	run the script in DBScrips to initialize database in sql server as well as install relevent sql client connector

3. 	run the following command in terminal:
	"cd DBScripts"
	"./create_db.sh"

	NOTE: password in create_db.sh is configured for out application user, please change to your own user password if error arises 

	or if you get an error run:

4. 	"sudo apt-get install default-libmysqlclient-dev"

5. 	in the console run the Makefile as follows:
	"make test"
	
	this will run the program to show the basic user controller functionality:
	- create a user and save to database
	- delete a user from database
	- receive credentials of user in database
	- update/insert json report into user database
	- save parsed GPS json data to database
	- show warning messages in case of querying non-existant users 







