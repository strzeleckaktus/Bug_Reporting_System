#include "header.h"

SQL_Services::SQL_Services() {   //Here we open connection to the specified database. 
    dir = "myDBcp.db";
    sqlite3_open(dir.c_str(), &db);
}

int SQL_Services::callback(void* NotUsed, int argc, char** argv, char** azColName) {  // basic callback to iterate over elements
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i]);
    }
    printf("\n");
    return 0;
}
int SQL_Services::login_callback(void* NotUsed, int argc, char** argv, char** azColName) {   //callback used in login function, it returns value 4 when password and login matches
    string check = argv[0];
    if (check == "admin" || check == "user") {
        return 3;
    }
    else {
        return 0;
    }
}
int SQL_Services::login_check_callback(void* NotUsed, int argc, char** argv, char** azColName) {  //callback used in login function, to check the permission level of user
    string check = argv[0];
    if (check == "admin") {
        return 3;
    }
    else {
        return 0;
    }
}
void SQL_Services::add(string _perm, string _login, string _password, int _a) {   //Here we have the function used to add users to the database
    char* errMsg = 0;
    string sql = "INSERT INTO USERS (ROLE, LOGIN, PASSWORD) VALUES ('" + _perm + "','" + _login + "','" + _password + "');";
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cout << "You have entered the invalid data. Aborting." << endl;
    }
    else {
        cout << "records created succesfully. " << endl;
    }

}
void SQL_Services::add(string _dev, string _desc, string _bugtype) {    // This is a function to add bugs to the database
    string sql = "INSERT INTO BUGS (DEV, TYPE, DESC) VALUES ('" + _dev + "','" + _bugtype + "','" + _desc + "');";
    int x = sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
    if (x != SQLITE_OK) {
        cout << "You have entered the invalid data. Aborting." << endl;
    }
    else {
        cout << "records created succesfully. " << endl;
    }
}
int SQL_Services::checkLogin(string _login, string _password) {
    string sql = "SELECT ROLE FROM USERS WHERE LOGIN = \"" + _login + "\" AND PASSWORD = \"" + _password + "\";";
    int x = sqlite3_exec(db, sql.c_str(), login_callback, NULL, NULL);
    if (x == 4) {
        sql = "SELECT ROLE FROM USERS WHERE LOGIN =\"" + _login + "\";";
        int xx = sqlite3_exec(db, sql.c_str(), login_check_callback, NULL, NULL);
        if (xx == 4) {
            return 2;
        }
        else {
            return 1;
        }
    }   
    return 0;
}
void SQL_Services::browse(string _database) {   // used to browse the records of the desired db
    
    string sql = "SELECT * FROM "+_database+";";
    int x = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
}
void SQL_Services::browse(string _database, char _type, string _parameter) {    // used to browse the records of the desired db
    string sql;
    if (_type == '4') {
        sql = "SELECT * FROM " + _database + " WHERE \"TYPE\" = \"" + _parameter + "\";";
    }
    else if (_type == '5') {
        sql = "SELECT * FROM " + _database + " WHERE \"DEV\" = \"" + _parameter + "\";";
    }
    int x = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
}
void SQL_Services::browse(string _database, char _type) {   // used to browse the records of the desired db
    string sql;
    if (_type == '2') {
        sql = "SELECT * FROM " + _database + " WHERE \"SOLVED\" = \"no\";";
    }
    else if (_type == '3') {
        sql = "SELECT * FROM " + _database + " WHERE \"APPROVAL\" = \"no\";";
    }
    else if (_type == '4') {
        sql = "SELECT * FROM " + _database + " WHERE \"ROLE\" = \"admin\";";
    }
    else if (_type == '5') {
        sql = "SELECT * FROM " + _database + " WHERE \"ROLE\" = \"user\";";
    }
    int x = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
}
void SQL_Services::approveBug(int _a) {   // this function is used to approve a bug
    string i;
    i = to_string(_a);
    string sql = "UPDATE BUGS set APPROVAL = \"yes\" where BUG_ID = " + i + ";";
    int x = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
}
void SQL_Services::remove(int _a, string _database) {   // this function is used to delete records from database
    string i;
    i = to_string(_a);
    string sql;
    if (_database == "BUGS") {
        sql = "DELETE from BUGS where BUG_ID = \"" + i + "\";";
    }
    else if (_database == "USERS") {
        sql = "DELETE from USERS where USER_ID = " + i + ";";
    }
    int x = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
}
void SQL_Services::editBug(int _a, string _update, string _sqltype) {  // this function is used to edit a bug
    string i;
    i = to_string(_a);
    string sql = "UPDATE BUGS set " + _sqltype + " = \"" + _update + "\" where BUG_ID = " + i + ";";
    system("pause");
    int x = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
}
void SQL_Services::bugSolve(int _a, char _b) {   // this function is used to mark the bug as solved
    string i;
    i = to_string(_a);
    string sql;
    if (_b == 'y') {
        sql = "UPDATE BUGS set SOLVED = \"yes\" where BUG_ID = " + i + ";";
    }
    else if (_b == 'n') {
        sql = "UPDATE BUGS set SOLVED = \"no\" where BUG_ID = " + i + ";";
    }
  
    int x = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
}