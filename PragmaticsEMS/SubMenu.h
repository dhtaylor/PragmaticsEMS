#pragma once
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

#include "Menu.h"

using namespace std;

// SubMenu Class - Inherits from Menu Class
class SubMenu : public Menu {
	private:
		/* Members */
		bool	edit;			// Boolean Value Indicating Menu Includes Edit Option

	public:
		/* Constructors */
		SubMenu(Employee& user, bool isEditable);

		/* Methods */
		void display();				// Function to Display SubMenu
		bool isEditable();			// Function Returning SubMenu Includes Edit Option

};