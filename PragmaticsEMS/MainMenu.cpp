#include "MainMenu.h"

/* Constructors */
MainMenu::MainMenu(Employee& user) {
	string role = user.getRole();

	addOption("View Profile");
	addOption("View Salary History");

	if (role == "Manager" || role == "Administrator")
		addOption("View Managed Employees");

	if (role == "Administrator") {
		addOption("View All Employees");
		addOption("Add New Employee");
		addOption("Remove Employee");
		addOption("Edit Employee");

	}

}


/* Methods */


/*
Display Main Menu Procedure (display)

Description: This procedure displays the Main Menu to the screen.
	This procedure overrides the display procedure from the Menu
	super class.

Input: N/A
Output: void

*/
void MainMenu::display() {
	system("cls");

	cout << "Pragmatics EMS - Main Menu" << endl;
	cout << endl;

	for (int i = 1; i < getOptionCount(); i++) {
		cout << i << ". " << getOption(i) << endl;
	}

	cout << "0. " << getOption(0) << endl;
	cout << endl;

	promptSelection();

}

