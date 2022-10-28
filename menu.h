#ifndef MENU_H_
#define MENU_H_

# include <string>
# include <iostream>
# include <stdexcept>	// cerr
# include <windows.h>	// Sleep() for windows OS
# include <unistd.h>	// Sleep() for Linux OS
# include <iomanip>		// setprecision
# include <regex>		// regex_match() and pattern (obj of regular expression)

using namespace std;

class Menu {

public:
	static int option;

	static void addHeader(string menuTitle, string opt0Title) {
		cout << menuTitle << endl;
		cout << "=================================================================" << endl;
		cout << "Enter 0 to \"" << opt0Title << "\"" << endl;
		cout << endl;
	}

	static void addSubHeader(string subMenuTitle) {
		cout << subMenuTitle << endl;
		cout << "=================================" << endl;
	}

	static void addSpace() {
		for (int i = 0; i < 50; i++) {
			cout << endl;
		}
	}

	//https://stackoverflow.com/questions/7753976/regular-expression-for-numbers-without-leading-zeros
	static bool isInteger(string user_input) {
		// allows zero or a valid non-zero integer only (for e.g, 009 not valid, 9 valid);
		const regex pattern("^[-]?(0|[1-9][0-9]*)$");
		if(! regex_match(user_input, pattern)) {
			return false;
		}
		else {
			return true;
		}
	}

	// https://stackoverflow.com/questions/10516967/regexp-for-a-double
	// modified pattern to match at most double with two decimal places
	static bool isDouble(string user_input) {
		// allows zero or a valid non-zero integer (for e.g, 009 not valid, 9 valid);
		// allow double values, period(.)
		const regex pattern("^[-]?(0|([1-9][0-9]*))(\\.[0-9]([0-9])?)?$");
		if(! regex_match(user_input, pattern)) {
			return false;
		}
		else {
			return true;
		}
	}

	template<typename T, typename U>
	static bool isInBetween(T min_val, T max_val, U valToCheck) {
		// catch out of range values
		if ( !(valToCheck >= min_val && valToCheck <= max_val) ) {
			return false;
		}
		else {
			return true;
		}
	}

	//https://stackoverflow.com/questions/15836681/regular-expression-to-allow-single-whitespace-between-words
	static bool isValidString(string user_input) {	// for Station Name and Sigthseeing Spots
		// only allow string with alphabets and either one space or hyphen between words or alphabet
		const regex pattern("[A-Za-z]+([ -][A-Za-z]+)*");
		if(! regex_match(user_input, pattern)) {
			return false;
		}
		else {
			return true;
		}
	}

	static bool isStringPureZero(string user_input) {
		// check if string is just "0", allows user to abort the subway registration anytime, Go Back Previous.
		const regex pattern("^[0]$");
		if(! regex_match(user_input, pattern)) {
			return false;
		}
		else {
			return true;
		}
	}

	static void showErrorMsg(string description) {
		cerr << description + ". Try Again\n" << endl;
		Sleep(100);
	}

	static void recordAndValidateOption(int min_val, int max_val, string inputTitle = "option") {
		cout << endl;
		while (true) {
			cout << "Enter " + inputTitle + ": ";
			string user_input;
			// read user_input as string including whitespaces
			getline(cin, user_input);
			// catch string with alphanumeric, whitespace characters, avert double values by catching period(.)
			if ( ! isInteger(user_input) ) {
				showErrorMsg("Invalid input");
				continue;
			}
			// convert user input to integer
			int int_val = stoi(user_input);
			// catch out of range values for menu option
			if ( ! isInBetween(min_val, max_val, int_val) ) {
				showErrorMsg("Option out of range");
				continue;
			}
			Menu::option = int_val;
			break;
		}
	}

	static void showCustomerMenu() {
		addHeader("Customer Menu", "Log Out");
		cout << "1. Discover Subway Routes" << endl;
		cout << "2. Search Subway Station Details" << endl;
		cout << "3. Calculate Travel Information" << endl;
		cout << "4. Purchase A Ticket" << endl;
		cout << "5. View Purchase History" << endl;
		cout << "6. Delete Purchase" << endl;
		recordAndValidateOption(0, 6);
	}

	static void showAdminMenu() {
		addHeader("Admin Menu", "Log Out");
		cout << "1. View All Station Details" << endl;
		cout << "2. Add New Subway Station" << endl;
		cout << "3. Modify Subway Station Information" << endl;
		cout << "4. View All Ticket Purchases" << endl;
		cout << "5. Sort Ticket Purchase According To Passenger Name" << endl;
		cout << "6. Search Customer Ticket Purchase" << endl;
		cout << "7. Modify Customer Ticket Purchase" << endl;
		cout << "8. Delete Customer Ticket Purchase" << endl;
		recordAndValidateOption(0, 7);
	}

	static void addExitMenu(string menuTitle) {
		cout << endl;
		cout << "=================================================================" << endl;
		cout << "Enter -1 to \"Exit To " << menuTitle << "\"" << endl;
	}

};

#endif
