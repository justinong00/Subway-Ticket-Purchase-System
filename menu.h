#ifndef MENU_H_
#define MENU_H_

# include <string>
# include <stdexcept>
#include<limits>

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
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
	}

	static void recordAndValidateOption(int min_val, int max_val) {
		while (true) {
			cout << endl;
			cout << "Enter option: ";
			cin >> option;
			// if user input is STRING
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Invalid input. Try Again" << endl;
			}
			// is user input is NOT WITHIN RANGE OF MENU OPTION VALUES
			else if ( !(option >= min_val && option <= max_val) ) {
				cout << "Option out of range. Try Again" << endl;
			}
			else
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
		recordAndValidateOption(1, 6);
	}

	static void addExitMenu(string menuTitle) {
		cout << endl;
		cout << "=================================================================" << endl;
		cout << "Enter -1 to \"Exit To " << menuTitle << "\"" << endl;
	}
};




#endif
