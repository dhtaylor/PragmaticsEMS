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

#include "Cache.h"


/* Statics */
const string Cache::EMP_FILE = "employees.txt";			// Constant String for Employee Data File Name
const string Cache::SALARY_FILE = "salaries.txt";		// Constant String for Salaries Data File Name


/* Private Methods */


/*
Load Salaries Procedure (loadSalaries)

Description: This procdure loads Salaries from the data file into an
	array for use throughout the system.

Input: N/A
Output: void

*/
void		Cache::loadSalaries() {
	string line;
	ifstream inFile;
	salaryCount = 0;

	inFile.open(SALARY_FILE.data());

	if (inFile.is_open()) {
		while (getline(inFile, line)) {
			istringstream str(line);

			salaries[salaryCount++] = Salary(str);

		}

	}

	inFile.close();

}


/*
Load Employees Procedure (loadEmployees)

Description: This procdure loads Employees from the data file into an
	array for use throughout the system.

Input: N/A
Output: void

*/
void		Cache::loadEmployees() {
	string line;
	ifstream inFile;
	employeeCount = 0;

	inFile.open(EMP_FILE.data());

	if (inFile.is_open()) {
		while (getline(inFile, line)) {
			istringstream str(line);
			employees[employeeCount++] = Employee(str);

		}

	}

	inFile.close();

	// Add Salary IDs to Employee Object
	for (int i = 0; i < salaryCount; i++) {
		int empIdx = findEmployeeById(salaries[i].getEmployeeId());

		if (empIdx >= 0)
			employees[empIdx].addSalary(salaries[i].getId());

	}

	// Add Direct Report IDs to Employee Object
	for (int i = 0; i < employeeCount; i++) {
		int mgrIdx = findEmployeeById(employees[i].getManagerId());

		if (mgrIdx >= 0)
			employees[mgrIdx].addReport(employees[i].getId());

	}

}


/*
Write Employees Procedure (writeEmployees)

Description: This procdure writes Employees from an array into a
	data file for persistant storage.

Input: N/A
Output: void

*/
void		Cache::writeEmployees() {
	ofstream outFile;

	outFile.open(EMP_FILE.data(), ios::trunc);

	if (outFile.is_open()) {

		for (int i = 0; i < employeeCount; i++) {
			outFile << employees[i].toString() << endl;
		}

	}

	outFile.close();

}


/*
Write Salaries Procedure (writeSalaries)

Description: This procdure writes Salaries from an array into a
data file for persistant storage.

Input: N/A
Output: void

*/
void		Cache::writeSalaries() {
	ofstream outFile;

	outFile.open(SALARY_FILE.data(), ios::trunc);

	if (outFile.is_open()) {

		for (int i = 0; i < salaryCount; i++) {
			outFile << salaries[i].toString() << endl;
		}

	}

	outFile.close();

}


/* Constructors */
Cache::Cache() {
	refresh();
}


/* Methods */


/*
Add New Employee Function (addEmployee)

Description: This function prompts the user for information to create
	a new user that will be added to the system.

Input: N/A
Output: Employee& user

*/
Employee&	Cache::addEmployee() {
	string fname;
	string lname;
	string role;
	string hireDate;
	float hRate;

	system("cls");

	cout << "Pragmatics EMS - Add Employee"
		<< endl
		<< endl;

	cin.ignore();

	cout << "Enter First Name: ";
	getline(cin, fname);

	cout << "Enter Last Name: ";
	getline(cin, lname);

	cout << "Enter Role: ";
	getline(cin, role);

	cout << "Enter Hire Date: ";
	getline(cin, hireDate);

	cout << "Enter an Hourly Rate: ";
	cin >> hRate;

	Employee user(fname, lname, role, hireDate);
	Salary pay(user.getId(), hRate, hireDate);

	user.addSalary(pay.getId());

	salaries[salaryCount++] = pay;
	employees[employeeCount++] = user;
	save();
	refresh();

	return employees[employeeCount - 1];

}


/*
Add New Direct Report to Employee Function (addReport)

Description: This procedure adds an existing Employee as a direct
	report to a manager.

Input: int mgrId, int empId
Output: void

*/
void		Cache::addReport(int mgrId, int empId) {
	int mgrIx = findEmployeeById(mgrId);
	int empIx = findEmployeeById(empId);

	employees[mgrIx].addReport(empId);
	employees[empIx].setManager(mgrId);

	save();
	refresh();

}


/*
Display All Employees Procedure (displayAllEmployees)

Description: This procedure displays all employees to the screen.

Input: N/A
Output: void

*/
void		Cache::displayAllEmployees() {
	system("cls");

	cout << "Pragmatics EMS - All Employees"
		<< endl
		<< endl;

	cout << left << setw(15) << "Employee ID"
		<< left << setw(30) << "Full Name"
		<< left << setw(15) << "Role"
		<< left << setw(15) << "Hire Date"
		<< left << setw(30) << "Manager"
		<< endl
		<< endl;

	for (int i = 0; i < employeeCount; i++) {
		int mgrId = employees[i].getManagerId();
		int mgrIdx = findEmployeeById(mgrId);

		cout << left << setw(15) << to_string(employees[i].getId())
			<< left << setw(30) << employees[i].getName()
			<< left << setw(15) << employees[i].getRole()
			<< left << setw(15) << employees[i].getHireDate()
			<< left << setw(30) << ((mgrIdx >= 0 ) ? employees[mgrIdx].getName() : "")
			<< endl;
	}

	cout << endl;

}


/*
Display Direct Reports for Employee Procedure (displayReports)

Description: This procedure displays direct reports for the given
	Employee to the screen.

Input: Employee& user
Output: void

*/
void		Cache::displayReports(Employee& user) {
	system("cls");

	cout << "Pragmatics EMS - Direct Reports"
		<< endl
		<< endl;

	if (user.getReportCount() > 0) {
		int* empReports = user.getReportIds();

		cout << left << setw(15) << "Employee ID"
			<< left << setw(30) << "Full Name"
			<< left << setw(15) << "Role"
			<< left << setw(15) << "Hire Date"
			<< endl
			<< endl;

		for (int i = 0; i < user.getReportCount(); i++) {
			int idx = findEmployeeById(empReports[i]);

			cout << left << setw(15) << to_string(employees[idx].getId())
				<< left << setw(30) << employees[idx].getName()
				<< left << setw(15) << employees[idx].getRole()
				<< left << setw(15) << employees[idx].getHireDate()
				<< endl;
		}

	}
	else {
		cout << "No Direct Reports Found" << endl;
	}

	cout << endl;

}


/*
Display Salary Details for Employee Procedure (displaySalaryDetails)

Description: This procedure displays salary details for the given
	Employee to the screen.

Input: Employee& user
Output: void

*/
void		Cache::displaySalaryDetails(Employee& user) {
	system("cls");

	cout << "Pragmatics EMS - Employee Salary History"
		<< endl
		<< endl;

	if (user.getSalaryCount() > 0) {
		int* empSalaries = user.getSalaryIds();

		cout << left << setw(20) << "Effective Date"
			<< left << setw(20) << "Hourly Rate"
			<< endl
			<< endl;

		for (int i = 0; i < user.getSalaryCount(); i++) {
			int idx = findSalaryById(empSalaries[i]);

			cout << setprecision(2) << fixed
				<< left << setw(20) << salaries[idx].getEffectiveDate()
				<< left << setw(20) << salaries[idx].getHourlyRate()
				<< endl;
		}

	}
	else {
		cout << "No Salary Information Found" << endl;
	}

	cout << endl;

}


/*
Edit Employee Procedure (editEmployee)

Description: This procedure lets the user edit select fields for the
	provided Employee.

Input: int empId
Output: void

*/
void		Cache::editEmployee(int empId) {
	int idx = findEmployeeById(empId);

	if (idx >= 0) {
		bool confirmed = false;
		char selection = 'n';
		string fname;
		string lname;
		string role;
		string hireDate;

		do {
			system("cls");

			cout << "Pragmatics EMS - Edit Employee"
				<< endl
				<< endl;

			cin.ignore();

			cout << "Enter Values as Prompted (Enter Accepts Existing Value)" << endl;
			cout << endl;

			cout << "Enter First Name (" << employees[idx].getFirstName() << "): ";
			getline(cin, fname);

			if (fname == "")
				fname = employees[idx].getFirstName();

			cout << "Enter Last Name (" << employees[idx].getLastName() << "): ";
			getline(cin, lname);

			if (lname == "")
				lname = employees[idx].getLastName();

			cout << "Enter Role (" << employees[idx].getRole() << "): ";
			getline(cin, role);

			if (role == "")
				role = employees[idx].getRole();

			cout << "Enter Hire Date (" << employees[idx].getHireDate() << "): ";
			getline(cin, hireDate);

			if (hireDate == "")
				hireDate = employees[idx].getHireDate();

			system("cls");

			cout << "Pragmatics EMS - Edit Employee"
				<< endl
				<< endl;

			cout << "The updated values will be as follows: " << endl;
			cout << "First Name: " << fname << endl;
			cout << "Last Name: " << lname << endl;
			cout << "Role: " << role << endl;
			cout << "Hire Date: " << hireDate << endl;
			cout << endl;

			cout << "Is this correct (y or n)? ";
			cin >> selection;

			if (tolower(selection) == 'y') {
				employees[idx].setFirstName(fname);
				employees[idx].setLastName(lname);
				employees[idx].setRole(role);
				employees[idx].setHireDate(hireDate);
				confirmed = true;
			}

		} while (!confirmed);

		save();
		refresh();

	}

}


/*
Find Employee by ID Function (findEmployeeById)

Description: This function takes an Employee ID and finds the index
	of that employee in the cache. This uses a binary search algorithm
	to find the location of the Employee.

Input: int empId
Output: int

*/
int			Cache::findEmployeeById(int empId) {
	int first = 0;
	int last = employeeCount - 1;
	int middle;

	while (first <= last) {
		middle = first + (last - first) / 2;

		if (employees[middle].getId() == empId)
			return middle;

		else if (employees[middle].getId() > empId)
			last = middle - 1;
		else
			first = middle + 1;

	}

	return -1;

}


/*
Find Employee by User Name Function (findEmployeeByUserName)

Description: This function takes a username and finds the index
of that employee in the cache. This uses a linear search algorithm
to find the location of the Employee.

Input: string uname
Output: int

*/
int			Cache::findEmployeeByUserName(string uname) {
	for (int i = 0; i < employeeCount; i++) {
		if (employees[i].getUserName() == uname)
			return employees[i].getId();

	}

	return -1;

}


/*
Find Salary by Salary ID Function (findSalaryById)

Description: This function takes a salary ID and finds the index
of that salary in the cache. This uses a linear search algorithm
to find the location of the Employee.

Input: int salaryId
Output: int

*/
int			Cache::findSalaryById(int salaryId) {
	int first = 0;
	int last = salaryCount - 1;
	int middle;

	while (first <= last) {
		middle = first + (last - first) / 2;

		if (salaries[middle].getId() == salaryId)
			return middle;

		else if (salaries[middle].getId() > salaryId)
			last = middle - 1;
		else
			first = middle + 1;

	}

	return -1;

}


/*
Refresh Cache Procedure (refresh)

Description: This procedure reloads the cache with salaries and
	employees.

Input: N/A
Output: void

*/
void		Cache::refresh() {
	loadSalaries();
	loadEmployees();
}


/*
Remove Employee Procedure (removeEmployee)

Description: This procedure prompts the user for an Employee to
	remove from the system and then removes that Employee.

Input: N/A
Output: void

*/
void		Cache::removeEmployee() {
	int empId;

	displayAllEmployees();

	cout << endl;

	cout << "Enter the EmployeeID for the Employee to Remove: ";
	cin >> empId;

	int idx = findEmployeeById(empId);

	if (idx >= 0) {
		// Remove Salaries
		int sCount = employees[idx].getSalaryCount();

		if (sCount > 0) {
			int* empSalaries = employees[idx].getSalaryIds();

			for (int i = sCount - 1; i >= 0; i--) {
				removeSalary(empId, empSalaries[i]);
			}

		}

		// Remove Direct Reports
		int rCount = employees[idx].getReportCount();

		if (rCount > 0) {
			int* reports = employees[idx].getReportIds();

			for (int i = rCount - 1; i >= 0; i--) {
				removeReport(empId, reports[i]);

			}

		}

		// Remove Employee
		for (int l = idx; l < employeeCount; l++) {
			employees[l] = employees[l + 1];
		}

		employeeCount--;

		save();
		refresh();

	}

}


/*
Remove Direct Report from Employee Procedure (removeReport)

Description: This procedure removes the specified Employee from
	their manager.

Input: int mgrId, int empId
Output: void

*/
void		Cache::removeReport(int mgrId, int empId) {
	int mix = findEmployeeById(mgrId);
	int eix = findEmployeeById(empId);

	employees[mix].removeReport(empId);
	employees[eix].setManager(0);

	save();
	refresh();

}

/*
Remove Salary from Employee Procedure (removeSalary)

Description: This procedure removes the specified Salary from
its employee.

Input: int empId, int salaryId
Output: void

*/
void		Cache::removeSalary(int empId, int salaryId) {
	int eix = findEmployeeById(empId);
	int six = findSalaryById(salaryId);

	for (int i = six; i < salaryCount; i++) {
		salaries[i] = salaries[i + 1];
	}

	employees[eix].removeSalary(salaryId);
	salaryCount--;

	save();
	refresh();

}


/*
Save Cache Procedure (save)

Description: This procedure writes cache items (Salaries and
	Employees) to disk for persistent storage.

Input: N/A
Output: void

*/
void		Cache::save() {
		writeEmployees();
		writeSalaries();
}


/*
Validate Employee Password Function (validatePassword)

Description: This function compares the provided password with the
	password of the specifed Employee.

Input: int empId, string pword
Output: bool

*/
bool		Cache::validatePassword(int empId, string pword) {
	int idx = findEmployeeById(empId);
	
	return (employees[idx].matchPassword(pword)) ? true : false;

}

/* Getters and Setters */


/*
Get Employee Reference Function (getEmployee)

Description: This function finds and returns an Employee reference
	for the given EmployeeId.

Input: int empId
Output: Employee&

*/
Employee&	Cache::getEmployee(int empId) {
	int idx = findEmployeeById(empId);
	return employees[idx];
}

