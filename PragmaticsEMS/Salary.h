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

#include <string>
#include <sstream>

using namespace std;

// Salary Class
class Salary {
	private:
		/* Statics */
		static int maxId;									// Current Maximum Salary ID

		/* Members */
		int		m_id;										// Salary ID
		int		m_employeeId;								// Salary Employee ID
		float	m_hourlyRate;								// Hourly Rate
		string	m_effectiveDate;							// Effective Date of Salary

	public:
		/* Statics */
		static int getMaxId();								// Function to Get Current Maximum Salary ID

		/* Constructors */
		Salary();
		Salary(int empId, float hrate, string edate);
		Salary(istringstream &data);

		/* Methods */
		string	toString();									// Function to Get Salary as String

		/* Getters and Setters */
		string	getEffectiveDate();							// Function to Get Salary Effective Date
		int		getEmployeeId();							// Function to Get Salary Employee ID
		float	getHourlyRate();							// Function to Get Salary Hourly Rate
		int		getId();									// Function to Get Salary ID

};
