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

#include <iostream>
#include <string>

#include "Employee.h"

using namespace std;

// Menu Class
class Menu {
	private:
		/* Statics */
		const static int MAX_OPTIONS = 10;				// Maximum Number of Options Allowed

		/* Members */
		int			optionCount;						// Total Number of Options
		string		options[MAX_OPTIONS];				// Array of Options
		int			selection;							// Menu Selection Value

	public:
		/* Constructors */
		Menu();

		/* Methods */
		virtual void	display() =0;					// Function to Display Menu (Virtual)
		void			addOption(string);				// Procedure to Add Options to Menu
		void			promptSelection();				// Procedure to Prompt for Selection


		/* Getters and Setters */
		string		getOption(int);						// Function to Get Option at Index
		int			getOptionCount();					// Function to Get Option Count
		int			getSelection();						// Function to Get Selection Value

};