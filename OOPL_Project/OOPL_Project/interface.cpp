#include "header.h"

Interface::Interface() {      // this is the interface function, while it is running the program is running
	runtime = true;
	usrAdmin = false;
	usrUser = false;
	menu = "loginMenu";
	while (runtime) {
		while (runtime && (!usrAdmin) && (!usrUser)) {
			system("CLS");
			if (menu == "loginMenu") { loginMenu(); }
			else if (menu == "login") { login(); }
		}
		while (runtime && usrAdmin) {
			system("CLS");
			if (menu == "adminMenu") { adminMenu(); }
			else if (menu == "browseBug") { browse("BUGS"); }
			else if (menu == "addBug") { addBug(); }
			else if (menu == "addUser") { addUser(); }
			else if (menu == "approveReq") { approveReq(); }
			else if (menu == "editBug") { editBug(); }
			else if (menu == "deleteBug") { remove("BUGS"); }
			else if (menu == "bugSolve") { bugSolve(); }
			else if (menu == "deleteUser") { remove("USERS"); }
			else if (menu == "browseUser") { browse("USERS"); }

		}
		while (runtime && usrUser) {
			system("CLS");
			if (menu == "usrMenu") { usrMenu(); }
			else if (menu == "browse") { browse("BUGS"); }
			else if (menu == "addBug") { addBug(); }
			else if (menu == "bugSolve") { bugSolve(); }
			else if (menu == "editBug") { editBug(); }
			else if (menu == "deleteBug") { remove("BUGS"); }
		}
	}

}
void Interface::returnToMenu() {  // this is a simple function to return to the main menu depending on whether you are user or admin
	if (usrUser) {
		menu = "usrMenu";
	}
	else if (usrAdmin) {
		menu = "adminMenu";
	}
	else {
		menu = "loginMenu";
	}
}
void Interface::loginMenu() {  // this is the login menu
	char a;
	cout << "1. login" << endl;
	cout << "q. exit" << endl;
	cin >> a;
	switch (a) {
	case '1':
		menu = "login";
		break;
	case 'q':
		runtime = false;
		break;
	default:
		wrongInput();
	}
}
void Interface::login() {    // login function is used to take care of logging in and checking whether the password is correct
	string login, password;
	cout << "login: ";
	cin >> login;
	cout << "password: ";
	cin >> password;
	int x = sql_services.checkLogin(login, password);
	if (x == 2) {
		usrAdmin = true;
		menu = "adminMenu";
		cout << "logged in as " << login << endl;
		system("pause");
	}
	else if (x == 1) {
		usrUser = true;
		menu = "usrMenu";
		cout << "logged in as " << login << endl;
		system("pause");
	}
	else {
		wrongInput();
	}
	
}
void Interface::adminMenu() {    // this is the main menu for admin
	char a;
	cout << "1. add user" << endl;
	cout << "2. browse users" << endl;
	cout << "3. delete user" << endl;
	cout << "4. browse bugs" << endl;
	cout << "5. add bug" << endl;
	cout << "6. edit bugs" << endl;
	cout << "7. remove bugs" << endl;
	cout << "8. approve pending requests" << endl;
	cout << "9. solve Bug" << endl;
	cout << "q. logout" << endl;
	cout << endl;
	cin >> a;
	switch (a) {
	case '1':
		menu = "addUser";
		break;
	case '2':
		menu = "browseUser";
		break;
	case '3':
		menu = "deleteUser";
		break;
	case '4':
		menu = "browseBug";
		break;
	case '5':
		menu = "addBug";
		break;
	case '6':
		menu = "editBug";
		break;
	case '7':
		menu = "deleteBug";
		break;
	case '8':
		menu = "approveReq";
		break;
	case '9':
		menu = "bugSolve";
		break;
	case 'q':
		menu = "loginMenu";
		usrAdmin = false;
		break;
	default:
		wrongInput();

		
	}
}
void Interface::usrMenu() {  // this is the user menu
	char a;
	cout << "1. browse bugs" << endl;
	cout << "2. add bug" << endl;
	cout << "3. edit bugs" << endl;
	cout << "4. remove bugs" << endl;
	cout << "5. solve bug" << endl;
	cout << "q. logout" << endl;
	cout << endl;
	cin >> a;
	switch (a) {
	case '1':
		menu = "browse";
		break;
	case '2':
		menu = "addBug";
		break;
	case '3':
		menu = "editBug";
		break;
	case '4':
		menu = "deleteBug";
		break;
	case '5':
		menu = "bugSolve";
		break;
	case 'q':
		menu = "loginMenu";
		usrUser = false;
		break;
	default:
		cout << "wrong input" << endl;
		break;
	}
}
void Interface::wrongInput(){  // function used to print an wrong input message
	system("CLS");
	cout << "You've provided wrong input" << endl;
	system("pause");
	returnToMenu();

}
void Interface::addBug() {  // function used to specify interface for add Bug functionality, and call the function to put the received data to database
	string dev, description, bugtype;
	int type;
	cout << "Who is reporting the bug?" << endl;
	cin.ignore();
	getline(cin, dev);
	system("CLS");
	cout << "What is the type of the bug? In case of different kind of bug, please provide description in specified field." << endl;
	cout << "1. Critical, program breaking" << endl;
	cout << "2. Major bug" << endl;
	cout << "3. Minor bug" << endl;
	cout << "4. Aesthetical bug, not impending the working of solution" << endl;
	cin >> type;
	if (type == 1) {
		bugtype = "Critical, program breaking";
	}
	else if (type == 2) {
		bugtype = "Major bug";
	}
	else if (type == 3) {
		bugtype = "Minor bug";
	}
	else if (type == 4) {
		bugtype = "Aesthetical bug, not impending the working of solution";
	}
	system("CLS");
	cout << "Please provide a description of encountered problem. " << endl;
	cin.ignore();
	getline(cin, description);
	sql_services.add(dev, description, bugtype);
	returnToMenu();

}
void Interface::addUser() {    //function used to specify interface for add User functionality, and call the function to put the received data to database
	string perm, login, password;
	cout << "login: ";
	cin >> login;
	cout << "password: ";
	cin >> password;
	cout << "Permission level: ";
	cin >> perm;
	if (perm != "admin" && perm != "user") {
		cout << "wrong permission level, please try again" << endl;
		system("pause");
		menu = "adminMenu";
	}
	sql_services.add(perm, login, password, 0);
	menu = "adminMenu";
	system("pause");
}
void Interface::browse(string _database) {  // simple function to call the function used to get the data from database
	char a;
	int type;
	string parameter;
	cout << "Specify what you want to browse" << endl;
	if (_database == "BUGS") {
		cout << "1. All bugs" << endl;
		cout << "2. Show all unsolved bugs" << endl;
		cout << "3. Show all unapproved bugs" << endl;
		cout << "4. Show specific kind of bugs" << endl;
		cout << "5. Show bugs submitted by specific person" << endl;
		cin >> a;
		switch (a) {
		case '1':
			sql_services.browse(_database);
			break;
		case '2':
			sql_services.browse(_database, a);
			break;
		case '3':
			sql_services.browse(_database, a);
			break;
		case '4':
			system("CLS");
			cout << "Choose what kind of bugs do you want to see" << endl;
			cout << "1. Critical, program breaking" << endl;
			cout << "2. Major bug" << endl;
			cout << "3. Minor bug" << endl;
			cout << "4. Aesthetical bug, not impending the working of solution" << endl;
			cin >> type;
			if (type == 1) {
				parameter = "Critical, program breaking";
			}
			else if (type == 2) {
				parameter = "Major bug";
			}
			else if (type == 3) {
				parameter = "Minor bug";
			}
			else if (type == 4) {
				parameter = "Aesthetical bug, not impending the working of solution";
			}
			system("CLS");
			sql_services.browse(_database, a, parameter);
			break;
		case '5':
			system("CLS");
			cout << "Write a name of the person who submitted the bug" << endl;
			cin.ignore();
			getline(cin, parameter);
			sql_services.browse(_database, a, parameter);
			break;
		default:
			cout << "wrong Input" << endl;
			break;
		}
	}
	else if (_database == "USERS") {
		cout << "1. All accounts" << endl;
		cout << "2. Show admin accounts" << endl;
		cout << "3. Show user accounts" << endl;
		cin >> a;
		switch (a) {
		case '1':
			sql_services.browse(_database);
			break;
		case '2':
			sql_services.browse(_database, '4');
			break;
		case '3':
			sql_services.browse(_database, '5');
			break;
		default:
			cout << "wrong Input" << endl;
			break;
		}
	}
	system("pause");
	returnToMenu();
}
void Interface::approveReq() {   // interface function to approve bug requests
	int a;
	sql_services.browse("BUGS");
	cout << "Please choose an ID of the bug you want to approve" << endl;
	cin >> a;
	sql_services.approveBug(a);
	returnToMenu();
}
void Interface::editBug() {   // function to call editBug() function from sql_services, to edit a specified bug in a specified field
	int a;
	char b;
	sql_services.browse("BUGS");
	cout << "Choose the ID of the bug that you want to edit" << endl;
	cin >> a;
	system("CLS");
	cout << "Choose what part do you want to edit:" << endl;
	cout << "1. Dev" << endl;
	cout << "2. Type" << endl;
	cout << "3. Description" << endl;
	cin >> b;
	system("CLS");
	string update;
	string sqltype;
	switch (b) {
	case '1':
		sqltype = "DEV";
		cout << "Who is reporting the bug?" << endl;
		cin.ignore();
		getline(cin, update);
		break;
	case '2':
		sqltype = "TYPE";
		int type;
		cout << "What is the type of the bug? In case of different kind of bug, please provide description in specified field." << endl;
		cout << "1. Critical, program breaking" << endl;
		cout << "2. Major bug" << endl;
		cout << "3. Minor bug" << endl;
		cout << "4. Aesthetical bug, not impending the working of solution" << endl;
		cin >> type;
		if (type == 1) {
			update = "Critical, program breaking";
		}
		else if (type == 2) {
			update = "Major bug";
		}
		else if (type == 3) {
			update = "Minor bug";
		}
		else if (type == 4) {
			update = "Aesthetical bug, not impending the working of solution";
		}
		break;
	case '3':
		sqltype = "DESC";
		cout << "Please provide a description of encountered problem. " << endl;
		cin.ignore();
		getline(cin, update);
		break;
	default:
		cout << "wrong input" << endl;
		returnToMenu();
		break;
	}
	sql_services.editBug(a, update, sqltype);
	returnToMenu();
}
void Interface::bugSolve() {    // function used to set bugs as solved
	int a;
	char b;
	sql_services.browse("BUGS");
	cout << "Choose the ID of the bug that you want to edit" << endl;
	cin >> a;
	system("CLS");
	cout << "If you want to set the bug as solved, press y, if you want to set it as unsolved, press n" << endl;
	cin >> b;
	sql_services.bugSolve(a, b);
	system("pause");
	returnToMenu();
}
void Interface::remove(string _database) {  // function used to delete a records from database
	int a;
	if (_database == "BUGS") {
		sql_services.browse(_database);
		cout << "Please choose an ID of the bug you want to remove" << endl;
		cin >> a;
		sql_services.remove(a, _database);
	}
	else if (_database == "USERS") {
		sql_services.browse(_database);
		cout << "Please choose an ID of the user you want to remove" << endl;
		cin >> a;
		sql_services.remove(a, _database);
	}
	returnToMenu();
}