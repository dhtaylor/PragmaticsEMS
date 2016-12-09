#include "Menu.h"

/* Constructors */
Menu::Menu() {
	for (int i = 0; i < MAX_OPTIONS; i++) {
		options[i] = "";
	}
	
	optionCount = 0;

	addOption("Exit");

	selection = 0;
}


/* Methods */


/*
Add Option to Menu Procedure (addOption)

Description: This procedure adds an optoin to the Menu.

Input: string value
Output: void

*/
void Menu::addOption(string value) {
	options[optionCount++] = value;
}


/*
Prompt for Menu Selection Procedure (promptSelection)

Description: This procedure prompts the user to select a Menu option.

Input: N/A
Output: void

*/
void Menu::promptSelection() {
	cout << "Please select an option: ";
	cin >> selection;

}



/* Getters and Setters */


/*
Get Menu Option Function (getOption)

Description: This function returns the Menu option for the given ID.

Input: int id
Output: string

*/
string Menu::getOption(int id) {
	return options[id];
}


/*
Get Menu Option Count Function (getOptionCount)

Description: This function returns the count of options for the Menu.

Input: N/A
Output: int

*/
int Menu::getOptionCount() {
	return optionCount;
}


/*
Get Menu Selection Function (getSelection)

Description: This function returns the selection for the Menu.

Input: N/A
Output: int

*/
int Menu::getSelection() {
	return selection;
}

