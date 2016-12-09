#include "Employee.h"
#include "Utility.h"

/* Statics */
int Employee::maxId = 0;


/*
Get Current Maximum Employee ID Function(getMaxId)

Description: This function returns the current maximum ID number for
	all Employees.

Input: N/A
Output: int

*/
int Employee::getMaxId() {
	return maxId;
}


/* Constructors */
Employee::Employee() {
	this->m_salaryCount = 0;
	this->m_reportCount = 0;
}

Employee::Employee(string fname, string lname, string role, string hdate) {
	this->m_id = ++maxId;
	this->m_userName = toLower(fname) + "." + toLower(lname);
	this->m_password = "Password-01";
	this->m_firstName = fname;
	this->m_lastName = lname;
	this->m_role = role;
	this->m_hireDate = hdate;
	this->m_managerId = 0;
	this->m_salaryCount = 0;
	this->m_reportCount = 0;
}

Employee::Employee(istringstream &data) {
	int id;
	string userName;
	string password;
	string firstName;
	string lastName;
	string hireDate;
	string role;
	int managerId;

	data >> id >> userName >> password >> firstName >> lastName >> hireDate >> role >> managerId;

	this->m_id = id;
	this->m_userName = userName;
	this->m_password = password;
	this->m_firstName = firstName;
	this->m_lastName = lastName;
	this->m_hireDate = hireDate;
	this->m_role = role;
	this->m_managerId = managerId;
	this->m_salaryCount = 0;
	this->m_reportCount = 0;

	if (id > maxId)
		maxId = id;

}


/* Methods */

/*
Add Salary to Employee Procedure (addSalary)

Description: This procedure adds the SalaryID to the Employee as
	belonging to the Employee.

Input: int salaryId
Output: void

*/
void	Employee::addSalary(int salaryId) {
	salaries[m_salaryCount++] = salaryId;
}


/*
Add Direct Report to Employee Procedure (addReport)

Description: This procedure adds the Direct Report Employee ID to the
	Employee as reporting to the Employee.

Input: int empId
Output: void

*/
void	Employee::addReport(int empId) {
	reports[m_reportCount++] = empId;
}


/*
Display Employee Profile Procedure (displayProfile)

Description: This procedure displays details about the Employee to
	the screen.

Input: N/A
Output: void

*/
void	Employee::displayProfile() {
	system("cls");

	cout << "Pragmatics EMS - Employee Profile" << endl;
	cout << endl;

	cout << left << setw(15) << "EmployeeID: "
		<< left << setw(50) << to_string(this->getId())
		<< endl;

	cout << left << setw(15) << "UserName: "
		<< left << setw(50) << m_userName
		<< endl;

	cout << left << setw(15) << "FirstName: "
		<< left << setw(50) << m_firstName
		<< endl;

	cout << left << setw(15) << "LastName: "
		<< left << setw(50) << m_lastName
		<< endl;

	cout << left << setw(15) << "Role: "
		<< left << setw(50) << m_role
		<< endl;

	cout << left << setw(15) << "HireDate: "
		<< left << setw(50) << m_hireDate
		<< endl;

	cout << endl;

}


/*
Compare Employee Password to String Function (matchPassword)

Description: This compares the given string with the Employee
	password and returns true if they match.

Input: string password
Output: bool

*/
bool	Employee::matchPassword(string password) {
	if (this->m_password == password)
		return true;
	else
		return false;
}


/*
Remove Direct Report from Employee Procedure (removeReport)

Description: This procedure removes the Direct Report Employee ID
	from the Employee as reporting to the Employee.

Input: int empId
Output: void

*/
void	Employee::removeReport(int empId) {
	for (int i = 0; i < m_reportCount; i++) {
		if (reports[i] == empId) {
			for (int j = i; j < m_reportCount; j++) {
				reports[j] = reports[j + 1];
			}

			m_reportCount--;

		}

	}

}


/*
Remove Salary from Employee Procedure (removeSalary)

Description: This procedure removes the SalaryID from the Employee as
	belonging to the Employee.

Input: int salaryId
Output: void

*/
void	Employee::removeSalary(int salaryId) {
	for (int i = 0; i < m_salaryCount; i++) {
		if (salaries[i] == salaryId) {
			for (int j = i; j < m_reportCount; j++) {
				reports[j] = reports[j + 1];
			}

			m_salaryCount--;

		}

	}

}


/*
Get Employee as String Function (toString)

Description: This function returns the Employee as a string.

Input: N/A
Output: void

*/
string	Employee::toString() {
	return to_string(this->getId())
		+ '\t' + m_userName
		+ '\t' + m_password
		+ '\t' + m_firstName
		+ '\t' + m_lastName
		+ '\t' + m_hireDate
		+ '\t' + m_role
		+ '\t' + to_string(m_managerId);

}


/* Getters and Setters */


/*
Get Employee First Name Function (getFirstName)

Description: This function returns the Employee First Name.

Input: N/A
Output: string

*/
string	Employee::getFirstName() {
	return m_firstName;
}


/*
Get Employee Hire Date Function (getHireDate)

Description: This function returns the Employee Hire Date.

Input: N/A
Output: string

*/
string	Employee::getHireDate() {
	return m_hireDate;
}


/*
Get Employee ID Function (getId)

Description: This function returns the Employee ID.

Input: N/A
Output: int

*/
int		Employee::getId() {
	return m_id;
}


/*
Get Employee Last Name Function (getLastName)

Description: This function returns the Employee Last Name.

Input: N/A
Output: string

*/
string	Employee::getLastName() {
	return m_lastName;
}


/*
Get Employee Manager ID Function (getManagerId)

Description: This function returns the Employee Manager ID.

Input: N/A
Output: int

*/
int		Employee::getManagerId() {
	return this->m_managerId;
}


/*
Get Employee Full Name Function (getName)

Description: This function returns the Employee Full Name.

Input: N/A
Output: string

*/
string	Employee::getName() {
	return m_firstName + ' ' + m_lastName;
}


/*
Get Employee Full Name Function (getName)

Description: This function returns the Employee Full Name.

Input: N/A
Output: string

*/
int		Employee::getReportCount() {
	return m_reportCount;
}


/*
Get Employee Direct Report IDs Function (getReportIds)

Description: This function returns the Employee Direct Report IDs.

Input: N/A
Output: int*

*/
int*	Employee::getReportIds() {
	return reports;
}


/*
Get Employee Role Function (getRole)

Description: This function returns the Employee Role.

Input: N/A
Output: string

*/
string	Employee::getRole() {
	return this->m_role;
}


/*
Get Employee Salary Count Function (getSalaryCount)

Description: This function returns the Employee Salary Count.

Input: N/A
Output: int

*/
int		Employee::getSalaryCount() {
	return m_salaryCount;
}


/*
Get Employee Salary IDs Function (getSalaryIds)

Description: This function returns the Employee Salary IDs.

Input: N/A
Output: int*

*/
int*	Employee::getSalaryIds() {
	return salaries;
}


/*
Get Employee Username Function (getUserName)

Description: This function returns the Employee Username.

Input: N/A
Output: string

*/
string	Employee::getUserName() {
	return this->m_userName;
}


/*
Set Employee First Name Function (setFirstName)

Description: This function sets the Employee First Name.

Input: string fname
Output: void

*/
void	Employee::setFirstName(string fname) {
	this->m_firstName = fname;
}


/*
Set Employee Hire Date Function (setHireDate)

Description: This function sets the Employee Hire Date.

Input: string hdate
Output: void

*/
void	Employee::setHireDate(string hdate) {
	this->m_hireDate = hdate;
}


/*
Set Employee Last Name Function (setLastName)

Description: This function sets the Employee Last Name.

Input: string lname
Output: void

*/
void	Employee::setLastName(string lname) {
	this->m_lastName = lname;
}


/*
Set Employee Manager ID Function (setManager)

Description: This function sets the Employee Manager ID.

Input: int mgrId
Output: void

*/
void	Employee::setManager(int mgrId) {
	this->m_managerId = mgrId;
}


/*
Set Employee Role Function (setRole)

Description: This function sets the Employee Role.

Input: string role
Output: void

*/
void	Employee::setRole(string role) {
	this->m_role = role;
}