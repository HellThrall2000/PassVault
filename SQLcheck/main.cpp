#include "stdfx.h"
#include "decryption.h"
#include "encryption.h"
#include "asciiart.h"
#include <mysql.h>
#include <iostream>


using namespace std;
int qstate;

int main()
{
	intro();
	int choice=0; // switch case choice
	string app;	  // stores app/service name 
	string emailid; // stores email id 
	string pass;	
	string query;
	string user1 = "";
	
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "root", "testdb", 3306, NULL, 0);
	if (conn) {
		puts("Succesful connection to database");
	
	}
	else {
	 
		puts("Connection to database has failed");
	}
	cout << "Enter secret username:		";
	cin >> user1; // vault master password input

	const string& user = user1; //this variable is used for all queries
	const string& key = user1; // this variable is used as key to pass in functions

	query = "CREATE TABLE IF NOT EXISTS " + user + " (app VARCHAR(50) NOT NULL,emailid VARCHAR(50) NOT NULL,pass VARCHAR(200) NOT NULL,PRIMARY KEY(app)); ";	//creates table if it doesnt exist
	const char* q = query.c_str(); //storing query
	qstate = mysql_query(conn, q); //connecting and executing query
	if (!qstate) {

		if (mysql_affected_rows(conn))
		{
			cout << "Password details added"; //query ran succesfully

		}



	}
	else
	{

		cout << "Query failed" << mysql_error(conn) << endl; // query didnt run

	}
	while (choice != 6) { // infinite loop menu driven with exit as an option
		cout << "\n1. New password entry \n2. Search password  \n3. Update password \n4. Delete password \n5. Show all passwords\n6. Delete Account\n7. Exit \n";
		cin >> choice;
		switch (choice) {
		case 1:
		{	
			emailid = "";
			app = "";
			pass = "";
			/*taking inputs*/
			cout << "Enter app/site name:	";
			cin >> app;
			cout << "Enter emailid used:	";
			cin >> emailid;
			cout << "Enter password to be saved:	";
			cin >> pass;
			/*encrypting*/
			pass = encryptor(pass,key);
			query = "INSERT INTO "+ user +" VALUES ( '" + app + "', '" + emailid + "', '" + pass + "'); "; //passing query
			 const char* q = query.c_str();

			qstate = mysql_query(conn, q);
			if (!qstate) {

				if (mysql_affected_rows(conn)) //query ran succesfully
				{
					cout << "Password details added";

				}



			}
			else
			{

				cout << "Query failed" << mysql_error(conn) << endl;// query didnt run

			}
			}
			break;

		case 2:
		{
		string name_search;
		string query2 = "";
		cout << "Enter app/site name:	";
		cin >> name_search;
		query2 = "SELECT * FROM "+ user +" WHERE app = ('" + name_search + "'); "; //query to search for password
		const char* q1 = query2.c_str();
		qstate = mysql_query(conn, q1);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{	
				cout << "-----------------------------------------------------------------------------------------------------------";
				cout << "\nApp/Website:" << row[0] << "\tE-mail ID:" << row[1] << "\t\tPassword:" << decryptor(row[2], key)<<"\n";
				cout << "-----------------------------------------------------------------------------------------------------------";
			}



		}
		else
		{

			cout << "Query failed" << mysql_error(conn) << endl;

		}
		}
		break;

		case 3:
		{

			string name_search;
			string new_pass;
			string query2 = "";
			cout << "Enter app/site name:	";
			cin >> name_search;

			cout << "Enter new password";
			cin >> new_pass;

			query2 = "UPDATE "+ user +" SET pass ='" + encryptor(new_pass,key) + "'  WHERE app = '" + name_search + "' ;"; //query to update password

			const char* q1 = query2.c_str();

			qstate = mysql_query(conn, q1);

			if (!qstate) {
				if (mysql_affected_rows(conn))

				{
					cout << "Updated password";

				}
			}
			else
			{

				cout << "Query failed" << mysql_error(conn) << endl;

			}
		}
		break;
		case 4:
		{
			string name_search;
			string query2 = "";
			cout << "Enter app/website entry to be removed:		";
			cin >> name_search;
			query2 = "DELETE from "+ user +" WHERE app ='" + name_search + "' ;"; // query to delete password record
			const char* q1 = query2.c_str();
			qstate = mysql_query(conn, q1);
			if (!qstate) {
				if (mysql_affected_rows(conn))
				{
					cout << "Deleted password entry";

				}



			}
			else
			{

				cout << "Query failed" << mysql_error(conn) << endl;

			}


		}
		break;
		case 5:
		{
			string query = "SELECT * FROM "+user; //query to view entire table
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate) {
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << "----------------------------------------------------------------------------------------------------------------------------------------------------";
					cout << "\nApp/Website:" << row[0]<<"\t"<< "E-mail ID:" << row[1] << "\t\t" << "Password:" << "	" << decryptor(row[2], key) << "\n"; 

				}
				cout << "----------------------------------------------------------------------------------------------------------------------------------------------------";
			}
			
			else
			{

				cout << "Query failed" << mysql_error(conn) << endl;

			}



		
		
		}
		break;
		case 6:
		{
			query = "DROP TABLE "+user+";"; // query to delete entire table/ user account
			const char* q = query.c_str();

			qstate = mysql_query(conn, q);
			if (!qstate) {
				del();
				if (mysql_affected_rows(conn))
				{
					
					exit;

				}



			}
			else
			{

				cout << "Query failed" << mysql_error(conn) << endl;

			}
		
		
		}
		break;
		case 7:
		{ 
			outro();
			exit(1); //exits program
		}

		default: cout << "/nInvalid choice";
	  }
			
		

		
	}
		
	return 0;
}// end of main