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
#include <fstream>

#include "Salary.h"
#include "Employee.h"

using namespace std;

// Data Management Class - Cache
class Cache {
private:
	/* Statics */
	const static string EMP_FILE;			// Constant String for Employee Data File Name
	const static string SALARY_FILE;		// Constant String for Salaries Data File Name
	const static int MAX_ITEMS = 100;		// Maximum Number of Items for Arrays

	/* Members */
	int			employeeCount = 0;			// Total Employee Count
	Employee	employees[MAX_ITEMS];		// Array of Employees
	Salary		salaries[MAX_ITEMS];		// Array of Salaries
	int			salaryCount = 0;			// Total Salaries Count

	/* Private Methods */
	void loadSalaries();					// Procedure to Load Salaries from Data File
	void loadEmployees();					// Procedure to Load Employees from Data File
	void writeSalaries();					// Procedure to Write Salaries to Data File
	void writeEmployees();					// Procedure to Write Employees to Data File

public:
	/* Constructors */
	Cache();

	/* Methods */
	Employee&	addEmployee();							// Function to Add a New Employee
	void		addReport(int mgrId, int empId);		// Procedure to Add a New Direct Report to Employee
	void		displayAllEmployees();					// Procedure to Display All Employees
	void		displayReports(Employee& user);			// Procedure to Display All Direct Reports for Employee
	void		displaySalaryDetails(Employee& user);	// Procedure to Display Salary Details for Employee
	void		editEmployee(int empId);				// Procedure to Edit Employee
	int			findEmployeeById(int empId);			// Function to Get Employee Index from Employee ID
	int			findEmployeeByUserName(string uname);	// Function to Get Employee Index from User Name
	int			findSalaryById(int salaryId);			// Function to Get Salary Index from Salary ID
	void		refresh();								// Procedure to Refresh the Cache from Disk
	void		removeEmployee();						// Procedure to Remove an Employee
	void		removeReport(int mgrId, int empId);		// Procedure to Remove a Direct Report from Employee
	void		removeSalary(int empId, int salaryId);	// Procedure to Remove a Salary from Employee
	void		save();									// Procedure to Save Data to File
	bool		validatePassword(int empId, string pword);	// Function to Validate Employee Password for Login

	/* Getters and Setters */
	Employee&	getEmployee(int empId);					// Function to Get Employee Reference from Employee ID

};