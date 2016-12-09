#include "Salary.h"

/* Statics */
int Salary::maxId = 0;


/*
Get Current Maximum Salary ID Function(getMaxId)

Description: This function returns the current maximum ID number for
all Salaries.

Input: N/A
Output: int

*/
int Salary::getMaxId() {
	return maxId;
}


/* Constructors */
Salary::Salary() {
	this->m_employeeId = 0;
	this->m_hourlyRate = 0.0f;
	this->m_effectiveDate = "01/01/1900";

}

Salary::Salary(int empId, float hrate, string edate) {
	this->m_id = ++maxId;
	this->m_employeeId = empId;
	this->m_hourlyRate = hrate;
	this->m_effectiveDate = edate;
}

Salary::Salary(istringstream &data) {
	int id;
	int employeeId;
	float hourlyRate;
	string effectiveDate;

	data >> id >> employeeId >> hourlyRate >> effectiveDate;

	this->m_id = id;
	this->m_employeeId = employeeId;
	this->m_hourlyRate = hourlyRate;
	this->m_effectiveDate = effectiveDate;

	if (id > maxId)
		maxId = id;

}


/* Methods */


/*
Get Salary as String Function (toString)

Description: This function returns the Salary as a string.

Input: N/A
Output: void

*/
string	Salary::toString() {
	return to_string(this->getId())
		+ '\t' + to_string(m_employeeId)
		+ '\t' + to_string(m_hourlyRate)
		+ '\t' + m_effectiveDate;

}


/* Getters and Setters */


/*
Get Salary Effective Date Function (getEffectiveDate)

Description: This function returns the Salary Effective Date.

Input: N/A
Output: string

*/
string	Salary::getEffectiveDate() {
	return this->m_effectiveDate;
}


/*
Get Salary Employee ID Function (getEmployeeId)

Description: This function returns the Salary Employee ID.

Input: N/A
Output: int

*/
int		Salary::getEmployeeId() {
	return this->m_employeeId;
}


/*
Get Salary Hourly Rate Function (getHourlyRate)

Description: This function returns the Salary Hourly Rate.

Input: N/A
Output: float

*/
float	Salary::getHourlyRate() {
	return this->m_hourlyRate;
}


/*
Get Salary ID Function (getId)

Description: This function returns the Salary ID.

Input: N/A
Output: int

*/
int		Salary::getId() {
	return m_id;
}
