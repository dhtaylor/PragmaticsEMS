/*
Pragmatic's Employee Management System (PragmaticsEMS.cpp)

CPSC 390, FALL, 2016
Group Members: Dandy Taylor, Kartik Patel
DL
Group Project: Beta
12/08/2016

The Pragmatics’ EMS is started as a user logs into the interface and
is presented with a view that depends on their roles within the
organization. Individual users will be able to view details about
their employment like hire date, promotions and title changes,
salary, and manager. Managers will be able to see details for their
own information as well as for those who directly report to them.
Administrators will be able to add and remove employees, change
titles, change managers, adjust salaries, as well as see their own
information and those of anyone they manage.

*/

#include <iostream>

#include "Cache.h"
#include "MainMenu.h"
#include "SubMenu.h"
#include "Employee.h"
#include "Salary.h"

using namespace std;

Employee& login();									// Function to Log User into System

void getMainMenu(Employee& user);					// Procedure to get the Main Menu
void getSubMenu(Employee& user, bool isEditable);	// Procedure to get Sub Menus

//void processMenu(Menu* menu, Employee& user);		// Procedure to process Menus (This is a
													// controller that routes to appropriate sub
													// procedure based on menu type. I am not using
													// this now, I just left it in because I had a
													// question out to Dr. Hamada about how getting this to work.

void processMainMenu(MainMenu& menu, Employee& user);	// Procedure to Process Main Menu Selections
void processSubMenu(SubMenu& menu, Employee& user);		// Procedure to Process Sub Menu Selections

Cache cache;											// Data Management Class Instance

int main() {

	Employee user;			// Employee Instance Representing Logged in User

	// Login User
	user = login();

	// Display Main Menu
	getMainMenu(user);

	return 0;

}


/*
Login Procedure (login)

Description: This procdure prompts an person to log into the system
	by asking for a user name and password. The user is searched for
	and if found the passwords compared. Valid results return a 
	reference to an Employee object for the logged in user.

Input: N/A
Output: Employee& user

*/
Employee& login() {
	string uname;
	string pword;
	bool invalid = false;

	for(;;) {
		system("cls");

		cout << "Pragmatics EMS - Login"
			<< endl
			<< endl;

		if (invalid)
			cout << "Invalid UserName/Password! Please Try Again." << endl << endl;

		// Prompt for username
		cout << "Enter UserName: ";
		cin >> uname;

		// Prompt for password
		cout << "Enter Password: ";
		cin >> pword;

		int empId = cache.findEmployeeByUserName(uname);

		if (empId > 0) {
			if (cache.validatePassword(empId, pword)) {
				return cache.getEmployee(empId);
			}

		}

		invalid = true;

	}

}


/*
Main Menu Display Procedure (getMainMenu)

Description: This procdure creates a new MainMenu object based on the
	user that is passed in and displays that to the screen. It then 
	makes a call to process the selection.

Input: Employee& user
Output: void

*/
void getMainMenu(Employee& user) {
	MainMenu mainMenu(user);
	mainMenu.display();
	processMainMenu(mainMenu, user);

}


/*
Sub Menu Display Procedure (getSubMenu)

Description: This procdure creates a new SubMenu object based on the
	user that is passed in and displays that to the screen. It then
	makes a call to process the selection.

Input: Employee& user, bool isEditable
Output: void

*/
void getSubMenu(Employee& user, bool isEditable) {
	SubMenu subMenu(user, isEditable);
	subMenu.display();
	processSubMenu(subMenu, user);

}


/*
Menu Processing Procedure (processMenu)

Description: This procdure takes a Menu object and Employee reference
	and routes them to the appropriate procedure for processing.

Input: Menu* menu, Employee& user
Output: void

*/
//void processMenu(Menu* menu, Employee& user) {
//	string menuType = typeid(menu).name();
//
//	if (menuType == "class MainMenu")
//		processMainMenu(menu, user);
//	else if (menuType == "class SubMenu")
//		processSubMenu(menu, user);
//
//}


/*
Main Menu Processing Procedure (processMainMenu)

Description: This procdure takes a MainMenu object and Employee reference
	and calls one of several actions based on the selection of the
	MainMenu object.

Input: MainMenu& menu, Employee& user
Output: void

*/
void processMainMenu(MainMenu& menu, Employee& user) {

	int selection = menu.getSelection();

	switch (selection) {
		case 0: {
			cache.save();
			exit(0);
		}
		case 1: {
			user.displayProfile();
			getSubMenu(user, true);
			break;
		}
		case 2: {
			cache.displaySalaryDetails(user);
			getSubMenu(user, false);
			break;
		}
		case 3: {
			cache.displayReports(user);
			getSubMenu(user, false);
			break;
		}
		case 4: {
			cache.displayAllEmployees();
			getSubMenu(user, false);
			break;
		}
		case 5: {
			Employee& emp = cache.addEmployee();
			cache.displayAllEmployees();
			getSubMenu(user, false);
			break;
		}
		case 6: {
			cache.removeEmployee();
			cache.displayAllEmployees();
			getSubMenu(user, false);
			break;
		}
		case 7: {
			int empId;

			cache.displayAllEmployees();

			cout << endl;

			cout << "Enter the EmployeeID for the Employee to Edit: ";
			cin >> empId;


			cache.editEmployee(empId);
			cache.displayAllEmployees();
			getSubMenu(user, false);
			break;
		}

	}

}


/*
Sub Menu Processing Procedure (processSubMenu)

Description: This procdure takes a SubMenu object and Employee reference
and calls one of several actions based on the selection of the
SubMenu object.

Input: SubMenu& menu, Employee& user
Output: void

*/
void processSubMenu(SubMenu& menu, Employee& user) {

	int selection = menu.getSelection();
	bool edit = menu.isEditable();

	switch (selection) {
		case 0: {
			cache.save();
			exit(0);
		}
		case 1: {
			getMainMenu(user);
			break;
		}
		case 2: {
			if (!edit) {
				getMainMenu(user);
			}
			else {
				int empId = user.getId();
				cache.editEmployee(empId);
				user = cache.getEmployee(empId);
				user.displayProfile();
				getSubMenu(user, true);
			}
			break;
		}

	}

}
