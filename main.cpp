# include <iostream>
# include <string>
# include <stdexcept>	// cerr
# include <iomanip>    	// setprecision
# include <windows.h>	// Sleep() for windows OS
# include <unistd.h>	// Sleep() for Linux OS
# include <regex>
# include "subway.h"
# include "doubly.h"
# include "menu.h"

using namespace std;

int Menu::option = 0;	// initializing static member variable from Menu class

// https://stackoverflow.com/questions/63238594/how-to-change-object-property-based-on-function-parameter-c
// pointer-to-member concept
// Purpose: catch used data from existing nodes, like name, id, etc..
// T is data type for the value to be checked
// U is the class of the object
// V is the custom class (E.g., Subway)
template<typename T, typename U, typename V>
bool isTaken (T valToCheck, U classObj, T V::*member) {
	for (int i = 0; i < classObj.getSize(); i++) {
		if (valToCheck == classObj.getNodeAtIndex(i)->data.*member) {
			return true;
		}
	}
	return false;
}

int main() {
	try {
		DoublyLinkedList<Subway> lst;
		lst.insertAtEnd(Subway(101, "Titiwangsa", "END-OF-LINE", "PWTC", 0, 0, 0, 4, 0.4, 3, "Zoo Negara"));
		lst.insertAtEnd(Subway(102, "PWTC", "Titiwangsa", "Sultan Ismail", 4, 0.4, 3, 8, 0.8, 7, "KLCC"));
		lst.insertAtEnd(Subway(103, "Sultan Ismail", "PWTC", "Masjid Jamek", 8, 0.8, 7, 8, 0.8, 7, "Eco Park"));
		lst.insertAtEnd(Subway(104, "Masjid Jamek", "Sultan Ismail", "Plaza Rakyat", 8, 0.8, 7, 6, 0.6, 5, "APU"));
		lst.insertAtEnd(Subway(105, "Plaza Rakyat", "Masjid Jamek", "Hang Tuah", 6, 0.6, 5, 10, 1, 9, "Midvalley"));
		lst.insertAtEnd(Subway(106, "Hang Tuah", "Plaza Rakyat", "Pudu", 10, 1, 9, 5, 0.5, 4, "Petronas Twin Towers"));
		lst.insertAtEnd(Subway(107, "Pudu", "Hang Tuah", "Chan Sow Lin", 5, 0.5, 4, 5, 0.5, 4, "One Utama"));
		lst.insertAtEnd(Subway(108, "Chan Sow Lin", "Pudu", "END-OF-LINE", 5, 0.5, 4, 0, 0, 0, "Sunway Pyramid"));

		// CUSTOMER FUNCTIONALITY
/*		while (true) {
			CustomerMenu:	// label for goto
			Menu::showCustomerMenu();
			Menu::addSpace();

			// 1. Discover Subway Routes
			if (Menu::option == 1) {
				while (true) {
					// Choose Route
					Menu::addHeader("Choose Route", "Go Back");
					string first_station = lst.getNodeAtIndex(0)->data.currentStationName;
					string last_station = lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName;
					cout << "1. " << first_station << " -> " << last_station << endl;
					cout << "2. " << last_station << " -> " << first_station << endl;
					Menu::recordAndValidateOption(0, 2);
					Menu::addSpace();
					// Check Choose Route Option
					if (Menu::option == 0){		// Go Back to Customer Menu
						break;
					}
					// Order of Stations
					else if (Menu::option == 1) {
						Menu::addHeader("Order of Stations", "Go Back");
						cout << "==START==" << endl;
						lst.showForward(2);
						cout << "==STOP==" << endl;
						Menu::addExitMenu("Customer Menu");
						Menu::recordAndValidateOption(-1, 0);	// -1 Exit, 0 Go Back Previous
						Menu::addSpace();
					}
					else {	// Menu::option == 2
						Menu::addHeader("Order of Stations", "Go Back");
						cout << "==START==" << endl;
						lst.showBackward(2);
						cout << "==STOP==" << endl;
						Menu::addExitMenu("Customer Menu");
						Menu::recordAndValidateOption(-1, 0);	// -1 Exit, 0 Go Back Previous
						Menu::addSpace();
					}
					// Check Order of Stations Option
					if (Menu::option == -1){
						goto CustomerMenu;	// Exit to Customer Menu
					}
					else	// Go Back to Choose Route
						continue;
				}
			}



			// 2. Search Subway Station Details
			else if (Menu::option == 2) {
				while (true) {
					// Select Station Detail
					Menu::addHeader("Select Station Detail", "Go Back");
					cout << "1. Sightseeing Spots" << endl;
					cout << "2. ID" << endl;
					cout << "3. Next And Previous Stops" << endl;
					cout << "4. Available Stops" << endl;
					Menu::recordAndValidateOption(0, 4);
					Menu::addSpace();
					// Check Select Station Detail Option
					if (Menu::option == 0){		// Go Back to Customer Menu
						break;
					}

					// Save Select Station Detail Option before updated by following (Select A Station)
					int stationDetailOpt = Menu::option;
					while (true) {
						// Select A Station
						Menu::addHeader("Select A Station", "Go Back");
						lst.showForward(7);
						Menu::recordAndValidateOption(0, lst.getSize());	// Station Selection (Select A Station)
						Menu::addSpace();
						if (Menu::option == 0) {			// Go Back to Select Station Detail
							break;
						}

						// Display According To Select Station Detail Option
						if (stationDetailOpt == 1) {		// Sightseeing Spots (Select Station Detail)
							Menu::addHeader("Sightseeing Spots For " + lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName, "Go Back");
							string sightseeingSpots = lst.getNodeAtIndex(Menu::option - 1)->data.nearbySightseeingSpots.empty() ? "None" : lst.getNodeAtIndex(Menu::option - 1)->data.nearbySightseeingSpots;
							cout << sightseeingSpots << endl;
						}
						else if (stationDetailOpt == 2) {	// ID (Select Station Detail)
							Menu::addHeader("ID For " + lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName, "Go Back");
							cout << lst.getNodeAtIndex(Menu::option - 1)->data.subwayId<< endl;
						}
						else if (stationDetailOpt == 3) {	// Next And Previous Stops (Select Station Detail)
							Menu::addHeader("Next And Previous Stops For " + lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName, "Go Back");
							Menu::addSubHeader("Previous Station");
							string prevStation = lst.getNodeAtIndex(Menu::option - 1)->data.previousStationName == "END-OF-LINE" ? "None. It is END-OF-LINE" : lst.getNodeAtIndex(Menu::option - 1)->data.previousStationName;
							cout << prevStation << endl;
							cout << endl;
							Menu::addSubHeader("Next Station");
							string nextStation = lst.getNodeAtIndex(Menu::option - 1)->data.nextStationName == "END-OF-LINE" ? "None. It is END-OF-LINE" : lst.getNodeAtIndex(Menu::option - 1)->data.nextStationName;
							cout << nextStation << endl;
						}
						else {								// Available Stops (Select Station Detail)
							Menu::addHeader("Available Stops For " + lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName, "Go Back");
							Menu::addSubHeader(lst.getNodeAtIndex(0)->data.currentStationName + " -> " + lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName);
							lst.showNextNodesAfterIndex(Menu::option - 1);
							cout << endl;
							Menu::addSubHeader(lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName + " -> " + lst.getNodeAtIndex(0)->data.currentStationName);
							lst.showPreviousNodesAfterIndex(Menu::option - 1);
						}

						// Check Option For Final Menu
						Menu::addExitMenu("Customer Menu");
						Menu::recordAndValidateOption(-1, 0);	// -1 Exit, 0 Go Back Previous
						Menu::addSpace();
						if (Menu::option == -1){
							goto CustomerMenu;	// Exit to Customer Menu
						}
						else	// Go Back to Select A Station
							continue;
					}
				}
			}



			// 3. View Travel Information
			else if (Menu::option == 3) {
				while (true) {
					// Select Start And End Stations
					int startStationOpt, endStationOpt;
					Menu::addHeader("Select Start And End Stations", "Go Back");
					lst.showForward(7);
					// Check Select Start And End Stations Option
					Menu::recordAndValidateOption(0, lst.getSize(), "Start Station");
					if (Menu::option == 0){		// Enter Start Station: 0, means want to Go Back to Customer Menu
						Menu::addSpace();
						break;
					}
					else
						startStationOpt = Menu::option;
					CustomerSelectEndStation:
					Menu::recordAndValidateOption(0, lst.getSize(), "End Station");
					if (Menu::option == 0){		// Enter End Station: 0, means want to Go Back to Customer Menu
						Menu::addSpace();
						break;
					}
					// catch SAME Start and End Stations
					else if (Menu::option == startStationOpt) {
						cerr << ("To-And-From Same Station? Try Again") << endl;
						Sleep(100);
						goto CustomerSelectEndStation;
					}
					else
						endStationOpt = Menu::option;
					Menu::addSpace();

					// Travel Information From {Start Station} to {End Station}
					Menu::addHeader("Travel Information From " + lst.getNodeAtIndex(startStationOpt - 1)->data.currentStationName + " to " + lst.getNodeAtIndex(endStationOpt - 1)->data.currentStationName, "Go Back");
					Menu::addSubHeader("Travel Distance");
					cout << lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, endStationOpt - 1, 1) << " km" << endl;	// returns Travel Distance
					cout << endl;
					Menu::addSubHeader("Travel Expenses");
					cout << setprecision(2) << fixed;	// show two decimal places, e.g., RM 4.50
					cout << "RM " << lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, endStationOpt - 1, 2) << endl;	// returns Travel Fare
					cout << endl;
					Menu::addSubHeader("Travel Time");
					cout << setprecision(0) << fixed;	// reset the setprecision output buffer to not affect following output
					cout << lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, endStationOpt - 1, 3) << " mins" << endl;	// returns Travel Time

					// Check Option For Final Menu
					Menu::addExitMenu("Customer Menu");
					Menu::recordAndValidateOption(-1, 0);	// -1 Exit, 0 Go Back Previous
					Menu::addSpace();
					if (Menu::option == -1){
						goto CustomerMenu;	// Exit to Customer Menu
					}
					else	// Go Back to Select A Station
						continue;
				}
			}
		}*/


		// ADMIN FUNCTIONALITY
		while (true) {
			AdminMenu:
			Menu::showAdminMenu();
			Menu::addSpace();

			// 1. Add New Subway Station
			if (Menu::option == 1) {
				while (true) {
					// Select New Station Location
					Menu::addHeader("Select New Station Location", "Go Back");
					cout << "1. Add As First Station" << endl;
					cout << "2. Add As Last Station" << endl;
					cout << "3. Add In Between Stations" << endl;
					Menu::recordAndValidateOption(0, 3);
					Menu::addSpace();
					// Check Select New Station Location Option
					if (Menu::option == 0)		// Go Back to Admin Menu
						break;

					// Assign Remaining Menu::Option to selectNewStationLocationOpt
					int selectNewStationLocationOpt = Menu::option;

					// 3. Add In Between Stations only	(one extra step to choose which location to add new station)
					if (selectNewStationLocationOpt == 3) {
						AdminSelectLocationPage:
						// Select Location
						Menu::addHeader("Select Location", "Go Back");
						Menu::addSubHeader("Between");
						lst.showForwardEachNodeAndItsNextNode();
						Menu::recordAndValidateOption(0, lst.getSize() - 1);	// -1 becasue for e.g, 7 routes from 8 stations
						Menu::addSpace();
						// Check Select Location Option
						if (Menu::option == 0)		// Go Back to Select New Station Location
							continue;
					}

					// Enter New Station Details
					Menu::addHeader("Enter New Station Details", "Go Back");
					string tempUserInput, stationName;
					string sightseeingSpots = "";
					int stationID;
					bool goBack = false;	// counter to track if user aborts the sunbway registration
					double stationDistToPrev, stationDistToNext, stationFareToPrev, stationFareToNext, stationTimeToPrev, stationTimeToNext;
					// Enter New Subway ID
					Menu::addSubHeader("Enter New Subway ID");
					while (true) {
						cout << "-> ";
						// read user_input as string including whitespaces
						getline(cin, tempUserInput);
						// 0, Go Back Previous -> user abort
						if ( Menu::isStringPureZero(tempUserInput) ) {
							goBack = true;
							Menu::addSpace();
							if (selectNewStationLocationOpt == 3)
								goto AdminSelectLocationPage;		// Go Back to Select Location
							else
								break;
						}
						// catch string with alphanumeric, whitespace and special characters, except '-' in the beginning
						if ( ! Menu::isInteger(tempUserInput) ) {
							Menu::showErrorMsg("Invalid input");
							continue;
						}
						// convert user input to integer
						stationID = stoi(tempUserInput);
						// assume ID can be only 1-9999, catch out of range values
						if ( ! Menu::isInBetween(1, 9999, stationID) ) {
							Menu::showErrorMsg("ID out of range (1-9999 only)");
							continue;
						}
						// catch used ID from doubly linked list
						if ( isTaken(stationID, lst, &Subway::subwayId) ) {
							Menu::showErrorMsg("Subway ID taken");
							continue;
						}
						// ! verified Subway ID
						cout << endl;
						// Enter New Station Name
						Menu::addSubHeader("Enter New Station Name");
						break;
					}
					while (! goBack) {
						cout << "-> ";
						// read user_input as string including whitespaces
						getline(cin, tempUserInput);
						// 0, Go Back Previous -> user abort
						if ( Menu::isStringPureZero(tempUserInput) ) {
							goBack = true;
							Menu::addSpace();
							if (selectNewStationLocationOpt == 3)
								goto AdminSelectLocationPage;		// Go Back to Select Location
							else
								break;
						}
						// only allow string with alphabets and either one space or hyphen between
						if ( ! Menu::isValidString(tempUserInput) ) {
							Menu::showErrorMsg("Invalid station name");
							continue;
						}
						// assume stationName cannot be alphabet
						if ( tempUserInput.length() < 2 || tempUserInput.length() > 15) {
							Menu::showErrorMsg("Invalid station name (must be 2-15 characters)");
							continue;
						}
						// catch used stationName from doubly linked list
						if ( isTaken(tempUserInput, lst, &Subway::currentStationName) ) {
							Menu::showErrorMsg("Station Name taken");
							continue;
						}
						// ! verified Station Name
						stationName = tempUserInput;
						cout << endl;
						// Enter {New Station}'s Travel Distance To {First Station} || {Last Station} || {Previous Station}
						if (selectNewStationLocationOpt == 1)			// Add As First Station
							Menu::addSubHeader("Enter " + stationName + "'s Travel Distance To " + lst.getNodeAtIndex(0)->data.currentStationName);
						else if (selectNewStationLocationOpt == 2)		// Add As Last Station
							Menu::addSubHeader("Enter " + stationName + "'s Travel Distance To " + lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName);
						else if (selectNewStationLocationOpt == 3)		//  Add In Between Stations -> this will be to {Previous Station}
							Menu::addSubHeader("Enter " + stationName + "'s Travel Distance To " + lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName);
						break;
					}
					while (! goBack) {
						cout << "-> ";
						// read user_input as string including whitespaces
						getline(cin, tempUserInput);
						// 0, Go Back Previous -> user abort
						if ( Menu::isStringPureZero(tempUserInput) ) {
							goBack = true;
							Menu::addSpace();
							if (selectNewStationLocationOpt == 3)
								goto AdminSelectLocationPage;		// Go Back to Select Location
							else
								break;		// Go Back to Select New Station Location
						}
						// catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
						if ( ! Menu::isDouble(tempUserInput) ) {
							Menu::showErrorMsg("Invalid input");
							continue;
						}
						// convert user input to double
						stationDistToPrev = stod(tempUserInput);
						// assume stationDistToPrev can be only 1-9999, catch out of range values
						if ( ! Menu::isInBetween(1, 9999, stationDistToPrev) ) {
							Menu::showErrorMsg("Distance out of range (1.0-9999 only)");
							continue;
						}
						// ! verified {New Station}'s Travel Distance To {First Station} || {Last Station} || {Previous Station}
						cout << endl;
						// Add As First Station & Add As Last Station will skip this because ONLY AFFECT DISTANCE OF ONE STATION
						if (selectNewStationLocationOpt == 3)
							// Enter {New Station}'s Travel Distance To {Next Station}
							Menu::addSubHeader("Enter " + stationName + "'s Travel Distance To " + lst.getNodeAtIndex(Menu::option)->data.currentStationName);
						break;
					}
					while (! goBack) {
						// Add As First Station & Add As Last Station will skip this for above same reason
						if (selectNewStationLocationOpt == 3) {
							cout << "-> ";
							// read user_input as string including whitespaces
							getline(cin, tempUserInput);
							// 0, Go Back Previous -> user abort
							if ( Menu::isStringPureZero(tempUserInput) ) {
								goBack = true;
								Menu::addSpace();
								goto AdminSelectLocationPage;		// Go Back to Select Location
							}
							// catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
							if ( ! Menu::isDouble(tempUserInput) ) {
								Menu::showErrorMsg("Invalid input");
								continue;
							}
							// convert user input to double
							stationDistToNext = stod(tempUserInput);
							// assume stationDistToNext can be only 1-9999, catch out of range values
							if ( ! Menu::isInBetween(1, 9999, stationDistToNext) ) {
								Menu::showErrorMsg("Distance out of range (1.0-9999 only)");
								continue;
							}
							// ! verified {New Station}'s Travel Distance To {Next Station}
							cout << endl;
						}
						// Enter {New Station}'s Travel Fare To {First Station} || {Last Station} || {Previous Station}
						if (selectNewStationLocationOpt == 1)			// Add As First Station
							Menu::addSubHeader("Enter " + stationName + "'s Travel Fare To " + lst.getNodeAtIndex(0)->data.currentStationName);
						else if (selectNewStationLocationOpt == 2)		// Add As Last Station
							Menu::addSubHeader("Enter " + stationName + "'s Travel Fare To " + lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName);
						else if (selectNewStationLocationOpt == 3)		//  Add In Between Stations -> this will be to {Next Station}
							Menu::addSubHeader("Enter " + stationName + "'s Travel Fare To " + lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName);
						break;
					}
					while (! goBack) {
						cout << "-> ";
						// read user_input as string including whitespaces
						getline(cin, tempUserInput);
						// 0, Go Back Previous -> user abort
						if ( Menu::isStringPureZero(tempUserInput) ) {
							goBack = true;
							Menu::addSpace();
							if (selectNewStationLocationOpt == 3)
								goto AdminSelectLocationPage;		// Go Back to Select Location
							else
								break;		// Go Back to Select New Station Location
						}
						// catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
						if ( ! Menu::isDouble(tempUserInput) ) {
							Menu::showErrorMsg("Invalid input");
							continue;
						}
						// convert user input to double
						stationFareToPrev = stod(tempUserInput);
						// assume stationFareToPrev can be only 1-9999, catch out of range values
						if ( ! Menu::isInBetween(1, 9999, stationFareToPrev) ) {
							Menu::showErrorMsg("Fare out of range (1.0-9999 only)");
							continue;
						}
						// ! verified {New Station}'s Travel Fare To {First Station} || {Last Station} || {Previous Station}
						cout << endl;
						// Add As First Station & Add As Last Station will skip this because ONLY AFFECT FARE OF ONE STATION
						if (selectNewStationLocationOpt == 3)
							// Enter {New Station}'s Travel Fare To {Next Station}
							Menu::addSubHeader("Enter " + stationName + "'s Travel Fare To " + lst.getNodeAtIndex(Menu::option)->data.currentStationName);
						break;
					}
					while (! goBack) {
						// Add As First Station & Add As Last Station will skip this for above same reason
						if (selectNewStationLocationOpt == 3) {
							cout << "-> ";
							// read user_input as string including whitespaces
							getline(cin, tempUserInput);
							// 0, Go Back Previous -> user abort
							if ( Menu::isStringPureZero(tempUserInput) ) {
								goBack = true;
								Menu::addSpace();
								goto AdminSelectLocationPage;		// Go Back to Select Location
							}
							// catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
							if ( ! Menu::isDouble(tempUserInput) ) {
								Menu::showErrorMsg("Invalid input");
								continue;
							}
							// convert user input to double
							stationFareToNext = stod(tempUserInput);
							// assume stationFareToNext can be only 1-9999, catch out of range values
							if ( ! Menu::isInBetween(1, 9999, stationFareToNext) ) {
								Menu::showErrorMsg("Fare out of range (1.0-9999 only)");
								continue;
							}
							// ! verified {New Station}'s Travel Fare To {Next Station}
							cout << endl;
						}
						// Enter {New Station}'s Travel Time To {First Station} || {Last Station} || {Previous Station}
						if (selectNewStationLocationOpt == 1)
							Menu::addSubHeader("Enter " + stationName + "'s Travel Time To " + lst.getNodeAtIndex(0)->data.currentStationName);
						if (selectNewStationLocationOpt == 2)
							Menu::addSubHeader("Enter " + stationName + "'s Travel Time To " + lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName);
						if (selectNewStationLocationOpt == 3)
							Menu::addSubHeader("Enter " + stationName + "'s Travel Time To " + lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName);
						break;
					}
					while (! goBack) {
						cout << "-> ";
						// read user_input as string including whitespaces
						getline(cin, tempUserInput);
						// 0, Go Back Previous -> user abort
						if ( Menu::isStringPureZero(tempUserInput) ) {
							goBack = true;
							Menu::addSpace();
							if (selectNewStationLocationOpt == 3)
								goto AdminSelectLocationPage;		// Go Back to Select Location
							else
								break;		// Go Back to Select New Station Location
						}
						// catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
						if ( ! Menu::isDouble(tempUserInput) ) {
							Menu::showErrorMsg("Invalid input");
							continue;
						}
						// convert user input to double
						stationTimeToPrev = stod(tempUserInput);
						// assume stationTimeToPrev can be only 1-9999, catch out of range values
						if ( ! Menu::isInBetween(1, 9999, stationTimeToPrev) ) {
							Menu::showErrorMsg("Time out of range (1.0-9999 only)");
							continue;
						}
						// ! verified {New Station}'s Travel Time To {First Station} || {Last Station} || {Previous Station}
						cout << endl;
						// Add As First Station & Add As Last Station will skip this because ONLY AFFECT TIME OF ONE STATION
						if (selectNewStationLocationOpt == 3)
							// Enter {New Station}'s Travel Time To {Next Station}
							Menu::addSubHeader("Enter " + stationName + "'s Travel Time To " + lst.getNodeAtIndex(Menu::option)->data.currentStationName);
						break;
					}
					while (! goBack) {
						if (selectNewStationLocationOpt == 3) {
							cout << "-> ";
							// read user_input as string including whitespaces
							getline(cin, tempUserInput);
							// 0, Go Back Previous -> user abort
							if ( Menu::isStringPureZero(tempUserInput) ) {
								goBack = true;
								Menu::addSpace();
								goto AdminSelectLocationPage;		// Go Back to Select Location
							}
							// catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
							if ( ! Menu::isDouble(tempUserInput) ) {
								Menu::showErrorMsg("Invalid input");
								continue;
							}
							// convert user input to double
							stationTimeToNext = stod(tempUserInput);
							// assume stationTimeToNext can be only 1-9999, catch out of range values
							if ( ! Menu::isInBetween(1, 9999, stationTimeToNext) ) {
								Menu::showErrorMsg("Time out of range (1.0-9999 only)");
								continue;
							}
							// ! verified {New Station}'s Travel Time To {Next Station}
							cout << endl;
						}
						// Enter {New Station}'s Sightseeing Spots
						Menu::addSubHeader("Enter " + stationName + "'s Sightseeing Spots ");
						break;
					}
					while (! goBack) {
						// FIRST: Number Of Locations
						cout << "-> How many locations to enter: ";
						// read user_input as string including whitespaces
						getline(cin, tempUserInput);
						// 0, Go Back Previous -> user abort
						if ( Menu::isStringPureZero(tempUserInput) ) {
							goBack = true;
							Menu::addSpace();
							if (selectNewStationLocationOpt == 3)
								goto AdminSelectLocationPage;	// Go Back to Select Location
							else
								break;		// Go Back to Select New Station Location
						}
						// catch string with alphanumeric, whitespace and special characters, except '-' in the beginning
						if ( ! Menu::isInteger(tempUserInput) ) {
							Menu::showErrorMsg("Invalid input");
							continue;
						}
						// convert user input to integer
						int numOfLocations;
						numOfLocations = stoi(tempUserInput);
						// assume Number Of Locations can be only 1-10, catch out of range values
						if ( ! Menu::isInBetween(1, 10, numOfLocations) ) {
							Menu::showErrorMsg("Number of locations is out of range (1-10 only)");
							continue;
						}
						// ! verified Number Of Locations
						cout << endl;
						// SECOND: Enter Each Location
						for (int i = 1; i <= numOfLocations; i++) {
							cout << "-> Location " << i << ": ";
							// read user_input as string including whitespaces
							getline(cin, tempUserInput);
							// 0, Go Back Previous -> user abort
							if ( Menu::isStringPureZero(tempUserInput) ) {
								goBack = true;
								Menu::addSpace();
								if (selectNewStationLocationOpt == 3)
									goto AdminSelectLocationPage;	// Go Back to Select Location
								else
									break;		// Go Back to Select New Station Location
							}
							// only allow string with alphabets and either one space or hyphen between
							if ( ! Menu::isValidString(tempUserInput) ) {
								Menu::showErrorMsg("Invalid sightseeing spot name");
								i--;
								continue;
							}
							// assume sightseeingSpotName cannot be alphabet
							if ( tempUserInput.length() == 1) {
								Menu::showErrorMsg("Invalid sightseeing spot name (must be 2-15 characters)");
								i--;
								continue;
							}
							// ! verified Each Location and concatenate them
							sightseeingSpots += tempUserInput + ", ";
						}
						break;
					}
					// after all subway details has been verified and admin didn't hit 0 (Go Back Previous -> abort) at SECOND: Enter Each Location
					if (! goBack) {
						// remove last two characters from sightseeingSpots because of additional ", "
						sightseeingSpots.erase(sightseeingSpots.length()-2);
						 // FIRST UPDATE the data for the affected stations,
						// THEN INSERT the new station to doubly linked list
						if (selectNewStationLocationOpt == 1) {			// Add As First Station
							// update the Ori First Station
							lst.updateNodeData(0, &Subway::previousStationName, stationName);
							lst.updateNodeData(0, &Subway::travelDistanceBetweenPreviousStation, stationDistToPrev);
							lst.updateNodeData(0, &Subway::travelFareBetweenPreviousStation, stationFareToPrev);
							lst.updateNodeData(0, &Subway::travelTimeBetweenPreviousStation, stationTimeToPrev);
							// insert New First Station
							lst.insertAtFront(Subway(stationID, stationName,
									"END-OF-LINE",			// No Previous Station
									lst.getNodeAtIndex(0)->data.currentStationName,				// Add Ori First Station As Next Station
									0, 0, 0,				// No Previous Travel Info
									stationDistToPrev, stationFareToPrev, stationTimeToPrev,	// because all Add First Station details done at Prev points, its save in those
									sightseeingSpots)
							);
						}
						else if (selectNewStationLocationOpt == 2) {	// Add As Last Station
							// update the Ori Last Station
							lst.updateNodeData(lst.getSize() - 1, &Subway::nextStationName, stationName);
							lst.updateNodeData(lst.getSize() - 1, &Subway::travelDistanceBetweenNextStation, stationDistToPrev);
							lst.updateNodeData(lst.getSize() - 1, &Subway::travelFareBetweenNextStation, stationFareToPrev);
							lst.updateNodeData(lst.getSize() - 1, &Subway::travelTimeBetweenNextStation, stationTimeToPrev);
							// insert New Last Station
							lst.insertAtEnd(Subway(stationID, stationName,
									lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName,		// Add Ori Last Station As Prev Station
									"END-OF-LINE",			// No Next Station
									stationDistToPrev, stationFareToPrev, stationTimeToPrev,	// because all Add Last Station details done at Prev points, its save in those
									0, 0, 0,				// No Next Travel Info
									sightseeingSpots)
							);
						}
						else if (selectNewStationLocationOpt == 3) {	// Add In Between Stations
							// update the affected Previous Station
							lst.updateNodeData(Menu::option - 1, &Subway::nextStationName, stationName);
							lst.updateNodeData(Menu::option - 1, &Subway::travelDistanceBetweenNextStation, stationDistToPrev);
							lst.updateNodeData(Menu::option - 1, &Subway::travelFareBetweenNextStation, stationFareToPrev);
							lst.updateNodeData(Menu::option - 1, &Subway::travelTimeBetweenNextStation, stationTimeToPrev);
							// update the affected Next Station
							lst.updateNodeData(Menu::option, &Subway::previousStationName, stationName);
							lst.updateNodeData(Menu::option, &Subway::travelDistanceBetweenPreviousStation, stationDistToNext);
							lst.updateNodeData(Menu::option, &Subway::travelFareBetweenPreviousStation, stationFareToNext);
							lst.updateNodeData(Menu::option, &Subway::travelTimeBetweenPreviousStation, stationTimeToNext);
							// insert New In Between Station
							lst.insertItemAt(Subway(stationID, stationName,
									lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName,
									lst.getNodeAtIndex(Menu::option)->data.currentStationName,
									stationDistToPrev, stationFareToPrev, stationTimeToPrev,
									stationDistToNext, stationFareToNext, stationTimeToNext,
									sightseeingSpots), Menu::option
							);
						}
						// message to notify admin user
						cout << "\nCONGRATS.NEW STATION ADDED!\n" << endl;
						// show updates subway list
						Menu::addSubHeader("New Salak Selatan Line");
						lst.showForwardAllInfoInTable();
						// Check Option For Final Menu
						Menu::addExitMenu("Admin Menu");
						Menu::recordAndValidateOption(-1, 0);	// -1 Exit, 0 Go Back Previous
						Menu::addSpace();
						if (Menu::option == -1){
							goto AdminMenu;	// Exit to Admin Menu
						}
						else {
							if (selectNewStationLocationOpt == 3)
								goto AdminSelectLocationPage;	// Go Back to Select Location
							else
								continue;		// Go Back to Select New Station Location
						}
					}
					else	// if admin hit 0 (Go Back Previous -> abort) during Enter {New Station}'s Sightseeing Spots -> SECOND: Enter Each Location
						continue;	// Go Back to Select New Station Location
				}
			}


			// 2. Modify Subway Station Information
			else if (Menu::option == 2) {
				cerr << "Not Done. Pending.." << endl;
			}
		}	// comment here
	}


	catch (const invalid_argument& e)
	{
		cerr << e.what()<< endl;
	}
	return 0;
}

