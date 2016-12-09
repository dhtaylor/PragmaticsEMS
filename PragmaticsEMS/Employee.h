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
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// Employee Class
class Employee {

	private:
		/* Statics */
		const static int MAX_SALARIES = 100;		// Maximum Number of Salaries to Track for an Employee
		const static int MAX_REPORTS = 10;			// Maximum Number of Reports to Track for an Employee
		static int maxId;							// Current Maximum ID of All Employees

		/* Members */
		int		m_id;								// ID of Employee
		string	m_userName;							// Username of Employee
		string	m_password;							// Password of Employee
		string	m_firstName;						// First Name of Employee
		string	m_lastName;							// Last Name of Employee
		string	m_hireDate;							// Hire Date of Employee
		string	m_role;								// Role of Employee
		int		m_managerId;						// Employee Manager's ID
		int		salaries[MAX_SALARIES];				// Array to Hold SalaryIDs of Employee
		int		m_salaryCount;						// Number of SalaryIDs Recorded
		int		reports[MAX_REPORTS];				// Array to Hold Direct Report Employee IDs
		int		m_reportCount;						// Number of Direct Report Employee IDs Recorded

	public:
		/* Statics */
		static int getMaxId();						// Function to Get Current Maximum Employee ID

		/* Constructors */
		Employee();
		Employee(string fname, string lname, string role, string hdate);
		Employee(istringstream &data);

		/* Methods */
		void	addSalary(int salaryId);			// Procedure to Add Salary to Employee
		void	addReport(int empId);				// Procedure to Add Direct Report to Employee
		void	displayProfile();					// Procedure to Display Employee Profile to Screen
		bool	matchPassword(string password);		// Function to Compare Password with String
		void	removeReport(int empId);			// Procedure to Remove Direct Report from Employee
		void	removeSalary(int salaryId);			// Procedure to Remove Salary from Employee
		string	toString();							// Function to Get Employee as String


		/* Getters and Setters */
		string	getFirstName();						// Function to Get Employee First Name
		string	getHireDate();						// Function to Get Employee Hire Date
		int		getId();							// Function to Get Employee ID
		string	getLastName();						// Function to Get Employee Last Name
		int		getManagerId();						// Function to Get Employee Manager ID
		string	getName();							// Function to Get Employee Name
		int		getReportCount();					// Function to Get Employee Direct Report Count
		int*	getReportIds();						// Function to Get Employee Direct Report Employee IDs
		string	getRole();							// Function to Get Employee Role
		int		getSalaryCount();					// Function to Get Employee Salary Count
		int*	getSalaryIds();						// Function to Get Employee Salary IDs
		string	getUserName();						// Function to Get Employee User Name
		void	setFirstName(string fname);			// Function to Set Employee First Name
		void	setHireDate(string hdate);			// Function to Set Employee Hire Date
		void	setLastName(string lname);			// Function to Set Employee Last Name
		void	setManager(int mgrId);				// Function to Set Employee Manager
		void	setRole(string role);				// Function to Set Employee Role

};
