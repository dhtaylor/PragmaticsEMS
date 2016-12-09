#include "SubMenu.h"

/* Constructors */
SubMenu::SubMenu(Employee& user, bool isEditable) {

	addOption("Return");

	if (isEditable)
		addOption("Edit");

	this->edit = isEditable;
}


/* Methods */

/*
Display SubMenu Procedure (display)

Description: This procedure displays the SubMenu to the screen.
	This procedure overrides the display procedure from the Menu
	super class.

Input: N/A
Output: void

*/
void SubMenu::display() {
	string opt;

	cout << endl;

	for (int i = 1; i < getOptionCount(); i++) {
		opt = "";
		opt += to_string(i) + ". " + getOption(i);
		cout << left << setw(15) << opt;

	}

	opt = "0. " + getOption(0);
	cout << opt << endl;
	cout << endl;

	promptSelection();

}


/*
Return isEditable Procedure (isEditable)

Description: This procedure returns true if the SubMenu is being used
	for an editable feature (i.e., the SubMenu should include a Edit
	option.

Input: N/A
Output: bool

*/
bool SubMenu::isEditable() {
	return edit;
}