# include <iostream>
# include <string>
# include <stdexcept>
# include "subway.h"
# include "doubly.h"
# include "menu.h"

using namespace std;

int Menu::option = 0;	// initializing static member variable from Menu class

void Insert() {

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


		while (true) {
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
					if (Menu::option == 0){		// Go Back to CUSTOMER MENU
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
						goto CustomerMenu;	// Exit to CUSTOMER MENU
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
					if (Menu::option == 0){		// Go Back to CUSTOMER MENU
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
							goto CustomerMenu;	// Exit to CUSTOMER MENU
						}
						else	// Go Back to Select A Station
							continue;
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

