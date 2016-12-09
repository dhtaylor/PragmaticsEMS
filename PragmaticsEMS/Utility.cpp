#include "Utility.h"

/* Functions */


/*
Lower Case string Type Function (toLower)

Description: This function takes a string data type and converts it
	to a lower case string. This is something that is not available
	by default in the c++ standard libraries.

Input: string str
Output: string

*/
string toLower(string str) {
	for (int i = 0; i < str.size(); i++) {
		str[i] = tolower(str[i]);
	}

	return str;

}