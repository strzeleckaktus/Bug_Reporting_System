#ifndef HEADER_H__
#define HEADER_H__
#include <string>
#include <iostream>
#include "sqlite/sqlite3.h"
using namespace std;

class SQL_Services {
private:
	sqlite3* db;
	std::string dir; 
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	static int login_callback(void* NotUsed, int argc, char** argv, char** azColName);
	static int login_check_callback(void* NotUsed, int argc, char** argv, char** azColName);
public:
	SQL_Services();
	void add(string _perm, string _login, string _password, int _a);
	int checkLogin(string _login, string _password);
	void add(string _dev, string _desc, string _bugtype);
	void browse(string _database, char _type, string _parameter);
	void browse(string _database, char _type);
	void browse(string _database);
	void approveBug(int _a);
	void remove(int _a, string _database);
	void editBug(int _a, string _update, string _sqltype);
	void bugSolve(int _a, char _b);
	~SQL_Services() {
		sqlite3_close(db);
	}
};

class Interface {
private:
	bool runtime;
	bool usrAdmin;
	bool usrUser;
	string menu;
	SQL_Services sql_services;
public:
	Interface();
	void loginMenu();  //done
	void login(); // done
	void adminMenu(); // done
	void usrMenu();  //done
	void addUser(); //done  
	void browse(string _database); //done
	void addBug(); //done
	void approveReq(); //done
	void editBug();
	void remove(string _database); //done
	void returnToMenu(); //done
	void wrongInput(); //done
	void bugSolve();
};


#endif