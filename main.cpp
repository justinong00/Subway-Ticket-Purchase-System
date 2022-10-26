# include <iostream>
# include <string>
# include <stdexcept>
# include <iomanip>      // std::setprecision
# include <windows.h>
# include <unistd.h>
# include <bits/stdc++.h>
# include <cctype>
# include <limits>
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
		lst.insertAtEnd(Subway(1, "Titiwangsa", "", "PWTC", 0, 0, 0, 4, 0.4, 3, "Zoo Negara"));
		lst.insertAtEnd(Subway(2, "PWTC", "Titiwangsa", "Sultan Ismail", 4, 0.4, 3, 8, 0.8, 7, "KLCC"));
		lst.insertAtEnd(Subway(3, "Sultan Ismail", "PWTC", "Masjid Jamek", 8, 0.8, 7, 8, 0.8, 7, "Eco Park"));
		lst.insertAtEnd(Subway(4, "Masjid Jamek", "Sultan Ismail", "Plaza Rakyat", 8, 0.8, 7, 6, 0.6, 5, "APU"));
		lst.insertAtEnd(Subway(5, "Plaza Rakyat", "Masjid Jamek", "Hang Tuah", 6, 0.6, 5, 10, 1, 9, "Midvalley"));
		lst.insertAtEnd(Subway(6, "Hang Tuah", "Plaza Rakyat", "Pudu", 10, 1, 9, 5, 0.5, 4, "Petronas Twin Towers"));
		lst.insertAtEnd(Subway(7, "Pudu", "Hang Tuah", "Chan Sow Lin", 5, 0.5, 4, 5, 0.5, 4, "One Utama"));
		lst.insertAtEnd(Subway(8, "Chan Sow Lin", "Pudu", "", 5, 0.5, 4, 0, 0, 0, "Sunway Pyramid"));

		// CUSTOMER FUNCTIONALITY
		/*while (true) {
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

					while (true) {
						// Select A Station
						Menu::addHeader("Select A Station", "Go Back");
						lst.showForward(7);
						int stationDetailOpt = Menu::option;	// Save Select Station Detail Option before updated by following
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
							string prevStation = lst.getNodeAtIndex(Menu::option - 1)->data.previousStationName.empty() ? "None. It is FIRST STOP" : lst.getNodeAtIndex(Menu::option - 1)->data.previousStationName;
							cout << prevStation << endl;
							cout << endl;
							Menu::addSubHeader("Next Station");
							string nextStation = lst.getNodeAtIndex(Menu::option - 1)->data.nextStationName.empty() ? "None. It is LAST STOP" : lst.getNodeAtIndex(Menu::option - 1)->data.nextStationName;
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
					Menu::recordAndValidateOption(0, lst.getSize(), "End Station");
					if (Menu::option == 0){		// Enter End Station: 0, means want to Go Back to Customer Menu
						Menu::addSpace();
						break;
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
					if (Menu::option == 0){		// Go Back to Admin Menu
						break;
					}

					else if (Menu::option == 3) {
						while (true) {
							// Select Location
							Menu::addHeader("Select Location", "Go Back");
							Menu::addSubHeader("Between");
							lst.showForwardEachNodeAndItsNextNode();
							Menu::recordAndValidateOption(0, lst.getSize() - 1);	// -1 becasue for e.g, 7 routes from 8 stations
							Menu::addSpace();

							// Enter New Station Details
							Menu::addHeader("Enter New Station Details", "Go Back");
							string tempUserInput, stationName;
							int stationID;
							bool goBack = false;	// counter to track if user aborts the sunbway registration
							double stationDistToPrev, stationDistToNext, stationFareToPrev, stationFareToNext, stationTimeToPrev, stationTimeToNext;
							while (true) {
								// Enter New Subway ID
								Menu::addSubHeader("Enter New Subway ID");
								cout << "-> ";
								// read user_input as string including whitespaces
								getline(cin, tempUserInput);
								// 0, Go Back Previous -> user abort
								if ( Menu::isStringPureZero(tempUserInput) ) {
									goBack = true;
									Menu::addSpace();
									break;
								}
								// catch string with alphanumeric and whitespace characters
								if ( ! Menu::isInteger(tempUserInput) ) {
									Menu::showErrorMsg("Invalid input");
									continue;
								}
								// convert user input to integer
								stationID = stoi(tempUserInput);	// implicitly removes + or - sign if have
								// assume ID can be only 1-10000, catch out of range values
								if ( ! Menu::isInBetween(1, 10000, stationID) ) {
									Menu::showErrorMsg("ID out of range (1-10000 only)");
									continue;
								}
								// catch used ID from doubly linked list
								if ( isTaken(stationID, lst, &Subway::subwayId) ) {
									Menu::showErrorMsg("Subway ID taken");
									continue;
								}
								// ! verified Subway ID
								cout << endl;
								break;
							}
							while (! goBack) {
								// Enter New Station Name
								Menu::addSubHeader("Enter New Station Name");
								cout << "-> ";
								// read user_input as string including whitespaces
								getline(cin, tempUserInput);
								// 0, Go Back Previous -> user abort
								if ( Menu::isStringPureZero(tempUserInput) ) {
									goBack = true;
									Menu::addSpace();
									break;
								}
								// only allow string with alphabets and either one space or hyphen between
								if ( ! Menu::isValidStationName(tempUserInput) ) {
									Menu::showErrorMsg("Invalid station name");
									continue;
								}
								// assume stationName cannot be alphabet
								if ( tempUserInput.length() == 1) {
									Menu::showErrorMsg("Invalid station name (2 characters or more needed)");
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
								break;
							}
							while (! goBack) {
								// Enter {New Station}'s Travel Distance To {Previous Station}
								Menu::addSubHeader("Enter " + stationName + "'s Travel Distance To " + lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName);
								cout << "-> ";
								// read user_input as string including whitespaces
								getline(cin, tempUserInput);
								// 0, Go Back Previous -> user abort
								if ( Menu::isStringPureZero(tempUserInput) ) {
									goBack = true;
									Menu::addSpace();
									break;
								}
								if ( ! Menu::isDouble(tempUserInput) ) {
									Menu::showErrorMsg("Invalid input");
									continue;
								}
								// convert user input to double
								stationDistToPrev = stod(tempUserInput);	// implicitly removes + or - sign if have
								// assume stationDistToPrev can be only 1-10000, catch out of range values
								if ( ! Menu::isInBetween(1, 10000, stationDistToPrev) ) {
									Menu::showErrorMsg("Distance out of range (1.0-10000 only)");
									continue;
								}
								// ! verified Subway ID
								cout << endl;
								break;
							}
						}
					}
				}
			}
		}
	}


	catch (const invalid_argument& e)
	{
		cerr << e.what()<< endl;
	}
	return 0;
}

