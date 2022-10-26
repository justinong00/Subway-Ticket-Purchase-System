#ifndef MENU_H_
#define MENU_H_

# include <string>
# include <limits>
# include <iostream>
# include <stdexcept>
# include <cstddef>
# include <windows.h>
# include <unistd.h>
# include <iomanip>
# include <cctype>
# include <algorithm>
# include <regex>

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

	static bool isInteger(string user_input) {
		// catch string with alphanumeric and whitespace characters, avert double values by catching period(.)
		const regex pattern("^[-+]?[0-9]+$");	//	cond: optional -/+ sign in str begin, must be digit in str end
		if(! regex_match(user_input, pattern)) {
			return false;
		}
		else {
			return true;
		}
	}

	// https://stackoverflow.com/questions/10516967/regexp-for-a-double
	static bool isDouble(string user_input) {
		// allows zero or a valid non-zero integer;
		// catch string with alphanumeric and whitespace characters
		const regex pattern("^[-+]?(0|([1-9][0-9]*))(\\.[0-9]+)?$");
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

	static bool isValidStationName(string user_input) {
		// only allow string with alphabets and either one space or hyphen between words or alphabet
		const regex pattern("[A-Za-z]+([ -][A-Za-z]+)?");
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
		while (true) {
			cout << endl;
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
		cout << "1. Add New Subway Station" << endl;
		cout << "2. Modify Subway Station Information" << endl;
		cout << "3. View All Ticket Purchases" << endl;
		cout << "4. Sort Ticket Purchase According To Passenger Name" << endl;
		cout << "5. Search Customer Ticket Purchase" << endl;
		cout << "6. Modify Customer Ticket Purchase" << endl;
		cout << "7. Delete Customer Ticket Purchase" << endl;
		recordAndValidateOption(0, 7);
	}

	static void addExitMenu(string menuTitle) {
		cout << endl;
		cout << "=================================================================" << endl;
		cout << "Enter -1 to \"Exit To " << menuTitle << "\"" << endl;
	}

};




#endif
