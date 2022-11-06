# include <iostream>
# include <string>
# include <stdexcept>	// cerr
# include <iomanip>    	// setprecision
# include <windows.h>	// Sleep() for windows OS
# include <unistd.h>	// Sleep() for Linux OS
# include <regex>
# include <ctime>

#include "Doubly.h"
# include "LinkedList.h"
# include "Menu.h"
# include "Ticket.h"
# include "Queue.h"
# include "Subway.h"

using namespace std;

int Menu::option = 0;	// initializing static member variable from Menu class

// https://stackoverflow.com/questions/33407444/restore-original-value-after-setprecision
// https://stackoverflow.com/questions/19198550/what-is-the-point-of-streamsize-prec-cout-precision-and-the-following-lines
// gets the default precision to allow manipulation of d.p and reset to default to precision
streamsize ss = cout.precision();

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
        User user = {};

        LinkedList<User> userLst;
        userLst.insertLast(Customer(1, "johndoe", "johnDoe123/", "012345678901", "johndoe@gmail.com"));
        userLst.insertLast(Admin(2, "janedoe", "janeDoe123/", "123456789012", "janedoe@gmail.com"));

        DoublyLinkedList<Subway> lst;
        lst.insertAtEnd(Subway(101, "Titiwangsa", "END-OF-LINE", "PWTC", 0, 0, 0, 4, 0.4, 3, "Zoo Negara"));
        lst.insertAtEnd(Subway(102, "PWTC", "Titiwangsa", "Sultan Ismail", 4, 0.4, 3, 8, 0.8, 7, "KLCC"));
        lst.insertAtEnd(Subway(103, "Sultan Ismail", "PWTC", "Majlis Jamek", 8, 0.8, 7, 8, 0.8, 7, "Eco Park"));
        lst.insertAtEnd(Subway(104, "Masjid Jamek", "Sultan Ismail", "Plaza Rakyat", 8, 0.8, 7, 6, 0.6, 5, "APU"));
        lst.insertAtEnd(Subway(105, "Plaza Rakyat", "Majlis Jamek", "Hang Tuah", 6, 0.6, 5, 10, 1, 9, "Midvalley"));
        lst.insertAtEnd(Subway(106, "Hang Tuah", "Plaza Rakyat", "Pudu", 10, 1, 9, 5, 0.5, 4, "Petronas Twin Towers"));
        lst.insertAtEnd(Subway(107, "Pudu", "Hang Tuah", "Chan Sow Lin", 5, 0.5, 4, 5, 0.5, 4, "One Utama"));
        lst.insertAtEnd(Subway(108, "Chan Sow Lin", "Pudu", "END-OF-LINE", 5, 0.5, 4, 0, 0, 0, "Sunway Pyramid"));

        LinkedList<Ticket> TLL;
        TLL.insertLast(Ticket("TR1", "TK1", "PWTC", "Hang Tuah", 3.20, 3, "bobby", "980918059873","Fri Nov 05 13:23:30 2021\n", "13:33"));
        TLL.insertLast(Ticket("TR2", "TK2", "Hang Tuah", "Majlis Jamek", 1.60, 454, "tommy", "870128039933","Wed Nov 06 16:13:39 2021\n", "16:38"));
        TLL.insertLast(Ticket("TR3", "TK3", "Pudu", "Majlis Jamek", 2.10, 3, "bobby", "980918059873","Sun Nov 07 14:05:23 2021\n", "14:34"));
        TLL.insertLast(Ticket("TR4", "TK4", "Chan Sow Lin", "Plaza Rakyat", 2.00, 321, "sally", "011202023588","Sun Nov 07 16:54:12 2021\n", "17:00"));
        TLL.insertLast(Ticket("TR5", "TK5", "Plaza Rakyat", "Hang Tuah", 1.00, 321, "sally", "011202023588","Sun Nov 07 18:44:12 2021\n", "18:52"));
        // CUSTOMER FUNCTIONALITY

        Queue<Ticket> q;
        q.enqueue(Ticket("TR1", "TK1", "PWTC", "Hang Tuah", 3.20,3, "bobby", "980918059873",
                         "Fri Nov 05 13:23:30 2021\n", "13:33"));
        q.enqueue(Ticket("TR2", "TK2", "Hang Tuah", "Majlis Jamek", 1.60, 454, "tommy", "870128039933",
                         "Wed Nov 06 16:13:39 2021\n", "16:38"));
        q.enqueue(Ticket("TR3", "TK3", "Pudu", "Majlis Jamek", 2.10, 3, "bobby", "980918059873",
                         "Sun Nov 07 14:05:23 2021\n", "14:34"));
        q.enqueue(Ticket("TR4", "TK4", "Chan Sow Lin", "Plaza Rakyat", 2.00, 321, "sally", "011202023588",
                         "Sun Nov 07 16:54:12 2021\n", "17:00"));
        q.enqueue(Ticket("TR5", "TK5", "Plaza Rakyat", "Hang Tuah", 1.00, 321, "sally", "011202023588",
                                 "Sun Nov 07 18:44:12 2021\n", "18:52"));


        while (true) {

            MainMenu:
            Menu::showMainMenu();
            Menu::addSpace();
            if (Menu::option == 0) break;


//            Login
            while (Menu::option == 1) {
                user = {};
                boolean usernameIsValid = false;
                string userInput;
                User tempUser;

//                Username validation
                while (true) {
                    Menu::addHeader("Login Menu", "Go Back");
                    cout << "Enter username: ";

                    getline(cin, userInput);

                    if (Menu::isStringOrZero(userInput)) {
                        Menu::option = 0;
                        Menu::addSpace();
                        break;
                    }

                    tempUser = userLst.getByUsername(userInput);
                    if (tempUser.username.empty()) {
                        Menu::showErrorMsg("User not found");
                        Menu::addSpace();
                        continue;
                    }

                    usernameIsValid = true;
                    Menu::addSpace();
                    break;
                }

//                Password validation
                while (usernameIsValid) {
                    Menu::addHeader("Login Menu", "Go Back");
                    cout << "Enter password: ";

                    getline(cin, userInput);

                    if (Menu::isStringOrZero(userInput)) {
                        Menu::option = 0;
                        Menu::addSpace();
                        break;
                    }

                    if (userInput != tempUser.password) {
                        Menu::showErrorMsg("Incorrect password");
                        Menu::addSpace();
                        continue;
                    }

                    user = tempUser;
                    break;
                }

                if ((Menu::option == 0) | !user.username.empty()) {
                    Menu::addSpace();
                    break;
                }
            }

//            Customer Registration
            while (Menu::option == 2 && user.username.empty()) {
                user = {};
                User tempUser;
                Customer newCustomer;
                string userInput, tempUsername, tempEmail, tempIc;

//                Username, Email, Ic
                while (true) {
//                    Enter username
                    Menu::addHeader("Registration Menu", "Go Back");
                    cout << "Enter username: ";

                    getline(cin, tempUsername);

                    if (Menu::isStringOrZero(tempUsername)) {
                        Menu::option = 0;
                        Menu::addSpace();
                        break;
                    }

//                    Enter email
                    cout << endl;
                    cout << "Enter email: ";

                    getline(cin, tempEmail);

                    if (Menu::isStringOrZero(tempUsername)) {
                        Menu::option = 0;
                        Menu::addSpace();
                        break;
                    }

//                    Enter ic
                    cout << endl;
                    cout << "Enter ic: ";

                    getline(cin, tempIc);

                    if (Menu::isStringOrZero(tempUsername)) {
                        Menu::option = 0;
                        Menu::addSpace();
                        break;
                    }

//                    Username, Email, Ic validation
                    if (!User::isValidUsername(tempUsername)) {
                        Menu::showErrorMsg("Invalid username");
                        Menu::addSpace();
                        continue;
                    } else if (!User::isValidEmail(tempEmail)) {
                        Menu::showErrorMsg("Invalid email");
                        Menu::addSpace();
                        continue;
                    } else if (!User::isValidIc(tempIc)) {
                        Menu::showErrorMsg("Invalid ic");
                        Menu::addSpace();
                        continue;
                    }

//                    Check if records already exist
                    tempUser = userLst.getByUsername(tempUsername);
                    if (!tempUser.username.empty()) {
                        Menu::showErrorMsg("Username already exists");
                        Menu::addSpace();
                        continue;
                    }
                    tempUser = userLst.getByEmail(tempEmail);
                    cout << tempUser.email << endl;
                    if (!tempUser.email.empty()) {
                        Menu::showErrorMsg("Email is in use");
                        Menu::addSpace();
                        continue;
                    }
                    tempUser = userLst.getByIc(tempIc);
                    if (!tempUser.ic.empty()) {
                        Menu::showErrorMsg("Ic is in use");
                        Menu::addSpace();
                        continue;
                    }


                    newCustomer.username = tempUsername;
                    newCustomer.email = tempEmail;
                    newCustomer.ic = tempIc;
                    Menu::addSpace();
                    break;
                }

//                Password validation
                while (!newCustomer.username.empty()) {
                    string tempPassword;
                    tempPassword = "";
                    Menu::addHeader("Registration Menu", "Go Back");
                    cout << "Enter password: ";
                    getline(cin, userInput);

                    if (Menu::isStringOrZero(userInput)) {
                        Menu::option = 0;
                        Menu::addSpace();
                        break;
                    }

                    if (!User::isValidPassword(userInput)) {
                        Menu::showErrorMsg("Invalid password");
                        Menu::addSpace();
                        continue;
                    }

                    tempPassword = userInput;
                    Menu::addSpace();

//                    Confirm password
                    while (true) {
                        Menu::addHeader("Registration Menu", "Go Back");
                        cout << "Re-enter password: ";
                        getline(cin, userInput);

                        if (Menu::isStringOrZero(userInput)) {
                            Menu::option = 0;
                            Menu::addSpace();
                            break;
                        }

                        if (tempPassword == userInput) {
                            newCustomer.password = tempPassword;
                            Menu::addSpace();
                            break;
                        }

                        Menu::showErrorMsg("Passwords do not match");
                        Menu::addSpace();
                    }

                    if (Menu::option == 0 && (tempPassword == "" | tempPassword.empty())) {
                        break;
                    }
                    else if (Menu::option == 0) continue;

                    newCustomer.password = tempPassword;
                    break;
                }

                if (!newCustomer.password.empty()) {
//                    generate new id
                    newCustomer.id = (userLst.getLast().id + 1);

                    user = Customer(newCustomer.id, newCustomer.username, newCustomer.password, newCustomer.ic,
                                    newCustomer.email);
                    userLst.insertLast(user);
                    Menu::showNotification("Account was registered successfully");
                    Menu::addSpace();
                    break;
                }

                if ((Menu::option == 0) | !user.username.empty()) {
                    Menu::addSpace();
                    break;
                }
            }

            if (user.username.empty()) continue;

            CustomerMenu:
            while (user.role.isCustomer()) {
                Menu::showCustomerMenu();
                Menu::addSpace();
                if (Menu::option == 0) break;

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
                        if (Menu::option == 0) {        // Go Back to Customer Menu
                            break;
                        }
                            // Order of Stations
                        else if (Menu::option == 1) {
                            Menu::addHeader("Order of Stations", "Go Back");
                            cout << "==START==" << endl;
                            lst.showForward(2);
                            cout << "==STOP==" << endl;
                            Menu::addExitMenu("Customer Menu");
                            Menu::recordAndValidateOption(-1, 0);    // -1 Exit, 0 Go Back Previous
                            Menu::addSpace();
                        } else {    // Menu::option == 2
                            Menu::addHeader("Order of Stations", "Go Back");
                            cout << "==START==" << endl;
                            lst.showBackward();
                            cout << "==STOP==" << endl;
                            Menu::addExitMenu("Customer Menu");
                            Menu::recordAndValidateOption(-1, 0);    // -1 Exit, 0 Go Back Previous
                            Menu::addSpace();
                        }
                        // Check Order of Stations Option
                        if (Menu::option == -1) {
                            goto CustomerMenu;    // Exit to Customer Menu
                        } else    // Go Back to Choose Route
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
                        if (Menu::option == 0) {        // Go Back to Customer Menu
                            break;
                        }

                        // Save Select Station Detail Option before updated by following (Select A Station)
                        int stationDetailOpt = Menu::option;
                        while (true) {
                            // Select A Station
                            Menu::addHeader("Select A Station", "Go Back");
                            lst.showForward(7);
                            Menu::recordAndValidateOption(0, lst.getSize());    // Station Selection (Select A Station)
                            Menu::addSpace();
                            if (Menu::option == 0) {            // Go Back to Select Station Detail
                                break;
                            }

                            // Display According To Select Station Detail Option
                            if (stationDetailOpt == 1) {        // Sightseeing Spots (Select Station Detail)
                                Menu::addHeader("Sightseeing Spots For " +
                                                lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName,
                                                "Go Back");
                                string sightseeingSpots = lst.getNodeAtIndex(
                                        Menu::option - 1)->data.nearbySightseeingSpots.empty() ? "None"
                                                                                               : lst.getNodeAtIndex(
                                                Menu::option - 1)->data.nearbySightseeingSpots;
                                cout << sightseeingSpots << endl;
                            } else if (stationDetailOpt == 2) {    // ID (Select Station Detail)
                                Menu::addHeader(
                                        "ID For " + lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName,
                                        "Go Back");
                                cout << lst.getNodeAtIndex(Menu::option - 1)->data.subwayId << endl;
                            } else if (stationDetailOpt == 3) {    // Next And Previous Stops (Select Station Detail)
                                Menu::addHeader("Next And Previous Stops For " +
                                                lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName,
                                                "Go Back");
                                Menu::addSubHeader("Previous Station");
                                string prevStation =
                                        lst.getNodeAtIndex(Menu::option - 1)->data.previousStationName == "END-OF-LINE"
                                        ? "None. It is END-OF-LINE" : lst.getNodeAtIndex(
                                                Menu::option - 1)->data.previousStationName;
                                cout << prevStation << endl;
                                cout << endl;
                                Menu::addSubHeader("Next Station");
                                string nextStation =
                                        lst.getNodeAtIndex(Menu::option - 1)->data.nextStationName == "END-OF-LINE"
                                        ? "None. It is END-OF-LINE" : lst.getNodeAtIndex(
                                                Menu::option - 1)->data.nextStationName;
                                cout << nextStation << endl;
                            } else {                                // Available Stops (Select Station Detail)
                                Menu::addHeader("Available Stops For " +
                                                lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName,
                                                "Go Back");
                                Menu::addSubHeader(lst.getNodeAtIndex(0)->data.currentStationName + " -> " +
                                                   lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName);
                                lst.showNextNodesAfterIndex(Menu::option - 1);
                                cout << endl;
                                Menu::addSubHeader(
                                        lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName + " -> " +
                                        lst.getNodeAtIndex(0)->data.currentStationName);
                                lst.showPreviousNodesAfterIndex(Menu::option - 1);
                            }

                            // Check Option For Final Menu
                            Menu::addExitMenu("Customer Menu");
                            Menu::recordAndValidateOption(-1, 0);    // -1 Exit, 0 Go Back Previous
                            Menu::addSpace();
                            if (Menu::option == -1) {
                                goto CustomerMenu;    // Exit to Customer Menu
                            } else    // Go Back to Select A Station
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
                        if (Menu::option ==
                            0) {        // Enter Start Station: 0, means want to Go Back to Customer Menu
                            Menu::addSpace();
                            break;
                        } else
                            startStationOpt = Menu::option;
                        CustomerSelectEndStation:
                        Menu::recordAndValidateOption(0, lst.getSize(), "End Station");
                        if (Menu::option == 0) {        // Enter End Station: 0, means want to Go Back to Customer Menu
                            Menu::addSpace();
                            break;
                        }
                            // catch SAME Start and End Stations
                        else if (Menu::option == startStationOpt) {
                            cerr << ("To-And-From Same Station? Try Again") << endl;
                            Sleep(100);
                            goto CustomerSelectEndStation;
                        } else
                            endStationOpt = Menu::option;
                        Menu::addSpace();

                        // Travel Information From {Start Station} to {End Station}
                        Menu::addHeader("Travel Information From " +
                                        lst.getNodeAtIndex(startStationOpt - 1)->data.currentStationName + " to " +
                                        lst.getNodeAtIndex(endStationOpt - 1)->data.currentStationName, "Go Back");
                        Menu::addSubHeader("Travel Distance");
                        cout << setprecision(1) << fixed;        // shows one d.p
                        cout << lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, endStationOpt - 1, 1) << " km"
                             << endl;    // returns Travel Distance
                        cout << endl;
                        Menu::addSubHeader("Travel Expenses");
                        cout << setprecision(2) << fixed;        // shows two d.p
                        cout << "RM " << lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, endStationOpt - 1, 2)
                             << endl;    // returns Travel Fare
                        cout << endl;
                        Menu::addSubHeader("Travel Time");
                        cout << setprecision(1) << fixed;
                        cout << lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, endStationOpt - 1, 3)
                             << " mins" << endl;    // returns Travel Time
                        cout.precision(ss);                    // resets to system's default precision

                        // Check Option For Final Menu
                        Menu::addExitMenu("Customer Menu");
                        Menu::recordAndValidateOption(-1, 0);    // -1 Exit, 0 Go Back Previous
                        Menu::addSpace();
                        if (Menu::option == -1) {
                            goto CustomerMenu;    // Exit to Customer Menu
                        } else    // Go Back to Select A Station
                            continue;
                    }
                }



                    // Amine and/or Shaun continue here
                    // 4. Purchase A Ticket
                else if (Menu::option == 4) {
                    while (true) {
                        // Select Start And End Stations
                        int startStationOpt, endStationOpt;
                        Menu::addHeader("Select Start And End Stations", "Go Back");
                        lst.showForward(7);
                        // Check Select Start And End Stations Option
                        Menu::recordAndValidateOption(0, lst.getSize(), "Start Station");
                        if (Menu::option ==
                            0) {        // Enter Start Station: 0, means want to Go Back to Customer Menu
                            Menu::addSpace();
                            break;
                        } else
                            startStationOpt = Menu::option;
                        CustomerSelectEndStationTP:
                        Menu::recordAndValidateOption(0, lst.getSize(), "End Station");
                        if (Menu::option == 0) {        // Enter End Station: 0, means want to Go Back to Customer Menu
                            Menu::addSpace();
                            break;
                        }
                            // catch SAME Start and End Stations
                        else if (Menu::option == startStationOpt) {
                            cerr << ("To-And-From Same Station? Try Again") << endl;
                            Sleep(100);
                            goto CustomerSelectEndStationTP;
                        } else
                            endStationOpt = Menu::option;
                        Menu::addSpace();

                        string TrID, TkID;
                        int ID;
                        //To set the Transaction and Ticket ID
                        if (TLL.getSize() == 0) {
                            TrID = "TR1";
                            TkID = "TK1";
                        } else {
                            TrID = TLL.tail->val.getTrID();
                            ID = (TrID[2] - 48) +
                                 1; //Gets the ascii value of the number and minuses it by 48 and plus 1 to get the next ID
                            TrID = "TR" + to_string(ID);
                            TkID = TLL.tail->val.getTkID();
                            ID = (TkID[2] - 48) + 1;
                            TkID = "Tk" + to_string(ID);
                        }
                        //Getting the current time stamp to calculate the Departure and Transaction Time
                        time_t now = time(0);
                        tm *ltm = localtime(&now);
                        int Hour = ltm->tm_hour;
                        int Min = ltm->tm_min;
                        //If the current minute is past 30 minutes then we will set the minute to 30
                        if (Min > 30) {
                            Min = Min - (Min - 30);
                        } else {
                            //Otherwise set the minute to 0
                            Min = Min - Min;
                        }
                        //If the station direction is the opposite
                        if ((endStationOpt - 1) < (startStationOpt - 1)) {
                            //Gets the time difference between the Start Station and the size of the subway linked list
                            Min = Min + lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, lst.getSize(), 3);
                        } else {
                            //Gets the time difference between the start and the start station
                            Min = Min + lst.getDataDifferenceBetweenTwoNodes(0, startStationOpt - 1, 3);
                        }
                        //If the Minute is less than the current Minute time, 30 mins is added
                        if (Min < ltm->tm_min) {
                            Min = Min + 30;
                        }
                        //Adds an hour and minus 30 minutes from the time if them Minute value is more than 60
                        if (Min > 60) {
                            Min = Min - 60;
                            Hour = Hour + 1;
                        }
                        //Creates the Ticket class
                        string Dtime;
                        if (Min < 10) {
                            Dtime = to_string(Hour) + ":0" + to_string(Min);
                        } else {
                            Dtime = to_string(Hour) + ":" + to_string(Min);
                        }
                        Ticket T1 = Ticket(TrID, TkID, lst.getNodeAtIndex(startStationOpt - 1)->data.currentStationName,
                                           lst.getNodeAtIndex(endStationOpt - 1)->data.currentStationName,
                                           lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, endStationOpt - 1,
                                                                                2), Dtime);
                        Menu::addHeader("Ticket Details From " +
                                        lst.getNodeAtIndex(startStationOpt - 1)->data.currentStationName + " to " +
                                        lst.getNodeAtIndex(endStationOpt - 1)->data.currentStationName, "Cancel");
                        cout << setprecision(2) << fixed;
                        T1.showTicketDetails();
                        Menu::addProceedMenu("Adding Customer Information");
                        Menu::recordAndValidateOption(0, 1);
                        Menu::addSpace();
                        //Adding customer information
                        if (Menu::option == 1) {
                            //Will change with user function
                            string cn, cic;
                            int cid;
                            cic = user.ic;
							cid = user.id;
							cn = user.username;
                            cout << "Adding customer information" << endl << endl;
                            T1.setCusInfo(cid, cn, cic);
                            //Calculating the estimated current arrival time
                            Menu::addHeader("Estimated Current Arrival From " +
                                            lst.getNodeAtIndex(startStationOpt - 1)->data.currentStationName + " to " +
                                            lst.getNodeAtIndex(endStationOpt - 1)->data.currentStationName, "Cancel");
                            double RideTime = lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1,
                                                                                   endStationOpt - 1, 3);
                            Min = Min + RideTime;
                            if (Min > 60) {
                                Min = Min - 60;
                                Hour = Hour + 1;
                            }
                            if (Min < 10) {
                                cout << Hour << ":0" << Min << endl;
                            } else {
                                cout << Hour << ":" << Min << endl;
                            }
                            cout.precision(ss);
                            Menu::addExitMenu("Customer Menu and Confirm Ticket Purchase");
                            Menu::recordAndValidateOption(-1, 0);
                            Menu::addSpace();
                            if (Menu::option == -1) {
                                cout << "Ticket Purchased" << endl << endl;
                                TLL.insertLast(T1);
                                q.enqueue(T1);
                                break;
                            }
                            break;
                        } else {    // Go Back to Select A Station
                            goto CustomerMenu;
                        }
                    }
                }

                    //5. View Purchase History
                else if (Menu::option == 5) {
                    while (true) {
                        Menu::addHeader("Your Purchase History", "Delete a Purchase");
                        Menu::addSubHeader(
                                "Transaction ID \tTicketID \tSource Station \tDestination \tTicket Amount \tDeparture Time \tCustomer ID \tCustomer Name \tCustomer IC \t\tTransaction Date and Time");
                        cout << setprecision(2) << fixed;
                        int CusID = user.id; // This is where Customer ID will get its variable (for now it was 626 for testing)
                        TLL.sortByTransID();
                        TLL.showByCusID(CusID); // Displays all purchase transaction of Customer
                        cout.precision(ss);
                        Menu::addExitMenu("Customer Menu");
                        Menu::recordAndValidateOption(-1, 0);
                        if (Menu::option == -1) {
                            Menu::addSpace();
                            break;
                        } else if (Menu::option == 0) {
                            //This is to delete a transaction
                            cout << endl << "Enter Transaction ID to be Delete or 0 to cancel: ";
                            string TransID;
                            int index;
                            getline(cin, TransID);
                            if (TransID == "0") { //IF 0 the system goes back to Customer Menus
                                Menu::addSpace();
                                goto CustomerMenu;
                            } else {
                                index = TLL.getIndex(TransID); //Finds index of transaction
                                if (index == -1) {//Transaction Does Not exist
                                    Menu::showErrorMsg("Transaction Does Not Exist");
                                    continue;
                                } else {
                                    if (TLL.get(index).getCusID() == CusID) {
                                        TLL.deleteAt(index);
                                        cout << endl << "Transaction Deleted";
                                    } else {
                                        //Transaction Exists but it is not the Customers
                                        cerr << endl << "You do not have that Transaction" << endl;
                                        continue;
                                    }
                                }
                                Menu::addExitMenu("Customer Menu");
                                Menu::recordAndValidateOption(-1, 0);
                                Menu::addSpace();
                                break;
                            }
                        }
                        break;
                    }
                }

                else if (Menu::option == 6) {
                    while (true) {
                        string userInput;
                        User tempUser;
                        int userIndex;

                        Menu::addHeader("Edit Personal Details", "Go Back");
                        cout << "1. Change username" << endl;
                        cout << "2. Change password" << endl;
                        cout << "3. Change ic" << endl;
                        cout << "4. Change email" << endl;
                        Menu::recordAndValidateOption(0, 4);
                        Menu::addSpace();

                        if (Menu::option == 0) { break; }

                        while (Menu::option <= 4 | Menu::option >= 1) {
                            if (Menu::option == 1) {
                                Menu::addHeader("Edit Personal Details - Change Username", "Go Back");
                                cout << "Username: " << user.username << endl;
                                cout << "Change to: ";
                            }
                            else if (Menu::option == 2) {
                                Menu::addHeader("Edit Personal Details - Change password", "Go Back");
                                cout << "Password: " << user.password << endl;
                                cout << "Change to: ";
                            }
                            else if (Menu::option == 3) {
                                Menu::addHeader("Edit Personal Details - Change ic", "Go Back");
                                cout << "Ic: " << user.ic << endl;
                                cout << "Change to: ";
                            }
                            else if (Menu::option == 4) {
                                Menu::addHeader("Edit Personal Details - Change email", "Go Back");
                                cout << "Email: " << user.email << endl;
                                cout << "Change to: ";
                            }

                            getline(cin, userInput);

                            if (Menu::isStringOrZero(userInput)) {
                                Menu::option = 0;
                                Menu::addSpace();
                                break;
                            }

                            if (Menu::option == 1 && !User::isValidUsername(userInput)) {
                                Menu::showErrorMsg("Invalid username");
                                Menu::addSpace();
                                continue;
                            }
                            else if (Menu::option == 2 && !User::isValidPassword(userInput)) {
                                Menu::showErrorMsg("Invalid password");
                                Menu::addSpace();
                                continue;
                            }
                            else if (Menu::option == 3 && !User::isValidIc(userInput)) {
                                Menu::showErrorMsg("Invalid ic");
                                Menu::addSpace();
                                continue;
                            }
                            else if (Menu::option == 4 && !User::isValidEmail(userInput)) {
                                Menu::showErrorMsg("Invalid email");
                                Menu::addSpace();
                                continue;
                            }


                            if (Menu::option == 1) {
                                tempUser = userLst.getByUsername(userInput);
                                if (!tempUser.username.empty()) {
                                    Menu::showErrorMsg("Username already exists");
                                    Menu::addSpace();
                                    continue;
                                }

                                user.username = userInput;
                            }
                            else if (Menu::option == 2) {
                                user.password = userInput;
                            }
                            else if (Menu::option == 3) {
                                tempUser = userLst.getByIc(userInput);
                                if (!tempUser.ic.empty()) {
                                    Menu::showErrorMsg("Ic is in use");
                                    Menu::addSpace();
                                    continue;
                                }

                                user.ic = userInput;
                            }
                            else if (Menu::option == 4) {
                                tempUser = userLst.getByEmail(userInput);
                                if (!tempUser.email.empty()) {
                                    Menu::showErrorMsg("Email is in use");
                                    Menu::addSpace();
                                    continue;
                                }

                                user.email = userInput;
                            }

                            bool isModified = userLst.modify(user);
                            if (isModified) {
                                Menu::showNotification("Details have been updated");
                                Menu::addSpace();
                                break;
                            }
                            else {
                                Menu::showErrorMsg("User not found");
                                Menu::addSpace();
                                continue;
                            }
                        }
                    }
                }
            }

            AdminMenu:
            while (user.role.isAdmin()) {
                Menu::showAdminMenu();
                Menu::addSpace();
                if (Menu::option == 0) break;

                if (Menu::option == 1) {
                    // Current Salak Selatan Line
                    Menu::addSubHeader("Current Salak Selatan Line");
                    cout << endl;
                    // Shows All Station Details according to Subway member variables (subway.h)
                    lst.showForwardAllInfoInTable();
                    // Check Option For Final Menu
                    Menu::addExitMenu("Admin Menu");
                    Menu::recordAndValidateOption(-1, -1);    // remove 0 for Go Back Previous since Exit is same page
                    Menu::addSpace();
                    continue;    // Exit to Admin Menu, technically its the same as Go Back Previous
                }



                    // 2. Add New Subway Station
                else if (Menu::option == 2) {
                    while (true) {
                        // Select New Station Location
                        Menu::addHeader("Select New Station Location", "Go Back");
                        cout << "1. Add As First Station" << endl;
                        cout << "2. Add As Last Station" << endl;
                        cout << "3. Add In Between Stations" << endl;
                        Menu::recordAndValidateOption(0, 3);
                        Menu::addSpace();
                        // Check Select New Station Location Option
                        if (Menu::option == 0)        // Go Back to Admin Menu
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
                            Menu::recordAndValidateOption(0, lst.getSize() -
                                                             1);    // -1 becasue for e.g, 7 routes from 8 stations
                            Menu::addSpace();
                            // Check Select Location Option
                            if (Menu::option == 0)        // Go Back to Select New Station Location
                                continue;
                        }

                        // Enter New Station Details
                        Menu::addHeader("Enter New Station Details", "Go Back");
                        string tempUserInput, stationName;
                        string sightseeingSpots = "";
                        int stationID;
                        bool goBack = false;    // counter to track if user aborts the sunbway registration
                        double stationDistToPrev, stationDistToNext, stationFareToPrev, stationFareToNext, stationTimeToPrev, stationTimeToNext;
                        // Enter New Subway ID
                        Menu::addSubHeader("Enter New Subway ID");
                        while (true) {
                            cout << "-> ";
                            // read user_input as string including whitespaces
                            getline(cin, tempUserInput);
                            // 0, Go Back Previous -> user abort
                            if (Menu::isStringPureZero(tempUserInput)) {
                                goBack = true;
                                Menu::addSpace();
                                if (selectNewStationLocationOpt == 3)
                                    goto AdminSelectLocationPage;        // Go Back to Select Location
                                else
                                    break;
                            }
                            // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning
                            if (!Menu::isInteger(tempUserInput)) {
                                Menu::showErrorMsg("Invalid input");
                                continue;
                            }
                            // convert user input to integer
                            stationID = stoi(tempUserInput);
                            // assume ID can be only 1-9999, catch out of range values
                            if (!Menu::isInBetween(1, 9999, stationID)) {
                                Menu::showErrorMsg("ID out of range (1-9999 only)");
                                continue;
                            }
                            // catch used ID from doubly linked list
                            if (isTaken(stationID, lst, &Subway::subwayId)) {
                                Menu::showErrorMsg("Subway ID taken");
                                continue;
                            }
                            // ! verified Subway ID
                            cout << endl;
                            // Enter New Station Name
                            Menu::addSubHeader("Enter New Station Name");
                            break;
                        }
                        while (!goBack) {
                            cout << "-> ";
                            // read user_input as string including whitespaces
                            getline(cin, tempUserInput);
                            // 0, Go Back Previous -> user abort
                            if (Menu::isStringPureZero(tempUserInput)) {
                                goBack = true;
                                Menu::addSpace();
                                if (selectNewStationLocationOpt == 3)
                                    goto AdminSelectLocationPage;        // Go Back to Select Location
                                else
                                    break;
                            }
                            // only allow string with alphabets and either one space or hyphen between
                            if (!Menu::isValidString(tempUserInput)) {
                                Menu::showErrorMsg("Invalid station name");
                                continue;
                            }
                            // assume stationName cannot be alphabet and > 15 characters
                            if (tempUserInput.length() < 2 || tempUserInput.length() > 15) {
                                Menu::showErrorMsg("Invalid station name (must be 2-15 characters)");
                                continue;
                            }
                            // catch used stationName from doubly linked list
                            if (isTaken(tempUserInput, lst, &Subway::currentStationName)) {
                                Menu::showErrorMsg("Station Name taken");
                                continue;
                            }
                            // ! verified Station Name
                            stationName = tempUserInput;
                            cout << endl;
                            // Enter {New Station}'s Travel Distance To {First Station} || {Last Station} || {Previous Station}
                            if (selectNewStationLocationOpt == 1)            // Add As First Station
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Distance To " +
                                                   lst.getNodeAtIndex(0)->data.currentStationName);
                            else if (selectNewStationLocationOpt == 2)        // Add As Last Station
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Distance To " +
                                                   lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName);
                            else if (selectNewStationLocationOpt ==
                                     3)        //  Add In Between Stations -> this will be to {Previous Station}
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Distance To " +
                                                   lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName);
                            break;
                        }
                        while (!goBack) {
                            cout << "-> ";
                            // read user_input as string including whitespaces
                            getline(cin, tempUserInput);
                            // 0, Go Back Previous -> user abort
                            if (Menu::isStringPureZero(tempUserInput)) {
                                goBack = true;
                                Menu::addSpace();
                                if (selectNewStationLocationOpt == 3)
                                    goto AdminSelectLocationPage;        // Go Back to Select Location
                                else
                                    break;        // Go Back to Select New Station Location
                            }
                            // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
                            if (!Menu::isDouble(tempUserInput)) {
                                Menu::showErrorMsg("Invalid input");
                                continue;
                            }
                            // convert user input to double
                            stationDistToPrev = stod(tempUserInput);
                            // assume stationDistToPrev can be only 1-9999, catch out of range values
                            if (!Menu::isInBetween(0.1, 9999.0, stationDistToPrev)) {
                                Menu::showErrorMsg("Distance out of range (0.1, 9999 only)");
                                continue;
                            }
                            // ! verified {New Station}'s Travel Distance To {First Station} || {Last Station} || {Previous Station}
                            cout << endl;
                            // Add As First Station & Add As Last Station will skip this because ONLY AFFECT DISTANCE OF ONE STATION
                            if (selectNewStationLocationOpt == 3)
                                // Enter {New Station}'s Travel Distance To {Next Station}
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Distance To " +
                                                   lst.getNodeAtIndex(Menu::option)->data.currentStationName);
                            break;
                        }
                        while (!goBack) {
                            // Add As First Station & Add As Last Station will skip this for above same reason
                            if (selectNewStationLocationOpt == 3) {
                                cout << "-> ";
                                // read user_input as string including whitespaces
                                getline(cin, tempUserInput);
                                // 0, Go Back Previous -> user abort
                                if (Menu::isStringPureZero(tempUserInput)) {
                                    goBack = true;
                                    Menu::addSpace();
                                    goto AdminSelectLocationPage;        // Go Back to Select Location
                                }
                                // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
                                if (!Menu::isDouble(tempUserInput)) {
                                    Menu::showErrorMsg("Invalid input");
                                    continue;
                                }
                                // convert user input to double
                                stationDistToNext = stod(tempUserInput);
                                // assume stationDistToNext can be only 1-9999, catch out of range values
                                if (!Menu::isInBetween(0.1, 9999.0, stationDistToNext)) {
                                    Menu::showErrorMsg("Distance out of range (0.1-9999 only)");
                                    continue;
                                }
                                // ! verified {New Station}'s Travel Distance To {Next Station}
                                cout << endl;
                            }
                            // Enter {New Station}'s Travel Fare To {First Station} || {Last Station} || {Previous Station}
                            if (selectNewStationLocationOpt == 1)            // Add As First Station
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Fare To " +
                                                   lst.getNodeAtIndex(0)->data.currentStationName);
                            else if (selectNewStationLocationOpt == 2)        // Add As Last Station
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Fare To " +
                                                   lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName);
                            else if (selectNewStationLocationOpt ==
                                     3)        //  Add In Between Stations -> this will be to {Next Station}
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Fare To " +
                                                   lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName);
                            break;
                        }
                        while (!goBack) {
                            cout << "-> ";
                            // read user_input as string including whitespaces
                            getline(cin, tempUserInput);
                            // 0, Go Back Previous -> user abort
                            if (Menu::isStringPureZero(tempUserInput)) {
                                goBack = true;
                                Menu::addSpace();
                                if (selectNewStationLocationOpt == 3)
                                    goto AdminSelectLocationPage;        // Go Back to Select Location
                                else
                                    break;        // Go Back to Select New Station Location
                            }
                            // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
                            if (!Menu::isDouble(tempUserInput)) {
                                Menu::showErrorMsg("Invalid input");
                                continue;
                            }
                            // convert user input to double
                            stationFareToPrev = stod(tempUserInput);
                            // assume stationFareToPrev can be only 1-9999, catch out of range values
                            if (!Menu::isInBetween(0.1, 9999.0, stationFareToPrev)) {
                                Menu::showErrorMsg("Fare out of range (0.1-9999 only)");
                                continue;
                            }
                            // ! verified {New Station}'s Travel Fare To {First Station} || {Last Station} || {Previous Station}
                            cout << endl;
                            // Add As First Station & Add As Last Station will skip this because ONLY AFFECT FARE OF ONE STATION
                            if (selectNewStationLocationOpt == 3)
                                // Enter {New Station}'s Travel Fare To {Next Station}
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Fare To " +
                                                   lst.getNodeAtIndex(Menu::option)->data.currentStationName);
                            break;
                        }
                        while (!goBack) {
                            // Add As First Station & Add As Last Station will skip this for above same reason
                            if (selectNewStationLocationOpt == 3) {
                                cout << "-> ";
                                // read user_input as string including whitespaces
                                getline(cin, tempUserInput);
                                // 0, Go Back Previous -> user abort
                                if (Menu::isStringPureZero(tempUserInput)) {
                                    goBack = true;
                                    Menu::addSpace();
                                    goto AdminSelectLocationPage;        // Go Back to Select Location
                                }
                                // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
                                if (!Menu::isDouble(tempUserInput)) {
                                    Menu::showErrorMsg("Invalid input");
                                    continue;
                                }
                                // convert user input to double
                                stationFareToNext = stod(tempUserInput);
                                // assume stationFareToNext can be only 1-9999, catch out of range values
                                if (!Menu::isInBetween(0.1, 9999.0, stationFareToNext)) {
                                    Menu::showErrorMsg("Fare out of range (0.1-9999 only)");
                                    continue;
                                }
                                // ! verified {New Station}'s Travel Fare To {Next Station}
                                cout << endl;
                            }
                            // Enter {New Station}'s Travel Time To {First Station} || {Last Station} || {Previous Station}
                            if (selectNewStationLocationOpt == 1)
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Time To " +
                                                   lst.getNodeAtIndex(0)->data.currentStationName);
                            if (selectNewStationLocationOpt == 2)
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Time To " +
                                                   lst.getNodeAtIndex(lst.getSize() - 1)->data.currentStationName);
                            if (selectNewStationLocationOpt == 3)
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Time To " +
                                                   lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName);
                            break;
                        }
                        while (!goBack) {
                            cout << "-> ";
                            // read user_input as string including whitespaces
                            getline(cin, tempUserInput);
                            // 0, Go Back Previous -> user abort
                            if (Menu::isStringPureZero(tempUserInput)) {
                                goBack = true;
                                Menu::addSpace();
                                if (selectNewStationLocationOpt == 3)
                                    goto AdminSelectLocationPage;        // Go Back to Select Location
                                else
                                    break;        // Go Back to Select New Station Location
                            }
                            // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
                            if (!Menu::isDouble(tempUserInput)) {
                                Menu::showErrorMsg("Invalid input");
                                continue;
                            }
                            // convert user input to double
                            stationTimeToPrev = stod(tempUserInput);
                            // assume stationTimeToPrev can be only 1-9999, catch out of range values
                            if (!Menu::isInBetween(0.1, 9999.0, stationTimeToPrev)) {
                                Menu::showErrorMsg("Time out of range (0.1-9999 only)");
                                continue;
                            }
                            // ! verified {New Station}'s Travel Time To {First Station} || {Last Station} || {Previous Station}
                            cout << endl;
                            // Add As First Station & Add As Last Station will skip this because ONLY AFFECT TIME OF ONE STATION
                            if (selectNewStationLocationOpt == 3)
                                // Enter {New Station}'s Travel Time To {Next Station}
                                Menu::addSubHeader("Enter " + stationName + "'s Travel Time To " +
                                                   lst.getNodeAtIndex(Menu::option)->data.currentStationName);
                            break;
                        }
                        while (!goBack) {
                            if (selectNewStationLocationOpt == 3) {
                                cout << "-> ";
                                // read user_input as string including whitespaces
                                getline(cin, tempUserInput);
                                // 0, Go Back Previous -> user abort
                                if (Menu::isStringPureZero(tempUserInput)) {
                                    goBack = true;
                                    Menu::addSpace();
                                    goto AdminSelectLocationPage;        // Go Back to Select Location
                                }
                                // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
                                if (!Menu::isDouble(tempUserInput)) {
                                    Menu::showErrorMsg("Invalid input");
                                    continue;
                                }
                                // convert user input to double
                                stationTimeToNext = stod(tempUserInput);
                                // assume stationTimeToNext can be only 1-9999, catch out of range values
                                if (!Menu::isInBetween(0.1, 9999.0, stationTimeToNext)) {
                                    Menu::showErrorMsg("Time out of range (0.1-9999 only)");
                                    continue;
                                }
                                // ! verified {New Station}'s Travel Time To {Next Station}
                                cout << endl;
                            }
                            // Enter {New Station}'s Sightseeing Spots
                            Menu::addSubHeader("Enter " + stationName + "'s Sightseeing Spots ");
                            break;
                        }
                        while (!goBack) {
                            // FIRST: Number Of Locations
                            cout << "-> How many locations to enter: ";
                            // read user_input as string including whitespaces
                            getline(cin, tempUserInput);
                            // 0, Go Back Previous -> user abort
                            if (Menu::isStringPureZero(tempUserInput)) {
                                goBack = true;
                                Menu::addSpace();
                                if (selectNewStationLocationOpt == 3)
                                    goto AdminSelectLocationPage;    // Go Back to Select Location
                                else
                                    break;        // Go Back to Select New Station Location
                            }
                            // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning
                            if (!Menu::isInteger(tempUserInput)) {
                                Menu::showErrorMsg("Invalid input");
                                continue;
                            }
                            // convert user input to integer
                            int numOfLocations;
                            numOfLocations = stoi(tempUserInput);
                            // assume Number Of Locations can be only 1-10, catch out of range values
                            if (!Menu::isInBetween(1, 10, numOfLocations)) {
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
                                if (Menu::isStringPureZero(tempUserInput)) {
                                    goBack = true;
                                    Menu::addSpace();
                                    if (selectNewStationLocationOpt == 3)
                                        goto AdminSelectLocationPage;    // Go Back to Select Location
                                    else
                                        break;        // Go Back to Select New Station Location
                                }
                                // only allow string with alphabets and either one space or hyphen between
                                if (!Menu::isValidString(tempUserInput)) {
                                    Menu::showErrorMsg("Invalid sightseeing spot name");
                                    i--;
                                    continue;
                                }
                                // assume sightseeingSpotName cannot be alphabet and > 15 characters
                                if (tempUserInput.length() < 2 || tempUserInput.length() > 15) {
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
                        if (!goBack) {
                            // remove last two characters from sightseeingSpots because of additional ", "
                            sightseeingSpots.erase(sightseeingSpots.length() - 2);
                            // FIRST UPDATE the data for the affected stations,
                            // THEN INSERT the new station to doubly linked list
                            if (selectNewStationLocationOpt == 1) {            // Add As First Station
                                // update the Ori First Station
                                lst.updateNodeData(0, &Subway::previousStationName, stationName);
                                lst.updateNodeData(0, &Subway::travelDistanceBetweenPreviousStation, stationDistToPrev);
                                lst.updateNodeData(0, &Subway::travelFareBetweenPreviousStation, stationFareToPrev);
                                lst.updateNodeData(0, &Subway::travelTimeBetweenPreviousStation, stationTimeToPrev);
                                // insert New First Station
                                lst.insertAtFront(Subway(stationID, stationName,
                                                         "END-OF-LINE",            // No Previous Station
                                                         lst.getNodeAtIndex(
                                                                 0)->data.currentStationName,                // Add Ori First Station As Next Station
                                                         0, 0, 0,                // No Previous Travel Info
                                                         stationDistToPrev, stationFareToPrev,
                                                         stationTimeToPrev,    // because all Add First Station details done at Prev points, its save in those
                                                         sightseeingSpots)
                                );
                            } else if (selectNewStationLocationOpt == 2) {    // Add As Last Station
                                // update the Ori Last Station
                                lst.updateNodeData(lst.getSize() - 1, &Subway::nextStationName, stationName);
                                lst.updateNodeData(lst.getSize() - 1, &Subway::travelDistanceBetweenNextStation,
                                                   stationDistToPrev);
                                lst.updateNodeData(lst.getSize() - 1, &Subway::travelFareBetweenNextStation,
                                                   stationFareToPrev);
                                lst.updateNodeData(lst.getSize() - 1, &Subway::travelTimeBetweenNextStation,
                                                   stationTimeToPrev);
                                // insert New Last Station
                                lst.insertAtEnd(Subway(stationID, stationName,
                                                       lst.getNodeAtIndex(lst.getSize() -
                                                                          1)->data.currentStationName,        // Add Ori Last Station As Prev Station
                                                       "END-OF-LINE",            // No Next Station
                                                       stationDistToPrev, stationFareToPrev,
                                                       stationTimeToPrev,    // because all Add Last Station details done at Prev points, its save in those
                                                       0, 0, 0,                // No Next Travel Info
                                                       sightseeingSpots)
                                );
                            } else if (selectNewStationLocationOpt == 3) {    // Add In Between Stations
                                // update the affected Previous Station
                                lst.updateNodeData(Menu::option - 1, &Subway::nextStationName, stationName);
                                lst.updateNodeData(Menu::option - 1, &Subway::travelDistanceBetweenNextStation,
                                                   stationDistToPrev);
                                lst.updateNodeData(Menu::option - 1, &Subway::travelFareBetweenNextStation,
                                                   stationFareToPrev);
                                lst.updateNodeData(Menu::option - 1, &Subway::travelTimeBetweenNextStation,
                                                   stationTimeToPrev);
                                // update the affected Next Station
                                lst.updateNodeData(Menu::option, &Subway::previousStationName, stationName);
                                lst.updateNodeData(Menu::option, &Subway::travelDistanceBetweenPreviousStation,
                                                   stationDistToNext);
                                lst.updateNodeData(Menu::option, &Subway::travelFareBetweenPreviousStation,
                                                   stationFareToNext);
                                lst.updateNodeData(Menu::option, &Subway::travelTimeBetweenPreviousStation,
                                                   stationTimeToNext);
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
                            cout << "\nCONGRATS. NEW STATION ADDED!" << endl;
                            // Check Option For Final Menu
                            Menu::addExitMenu("Admin Menu");
                            Menu::recordAndValidateOption(-1, 0);    // -1 Exit, 0 Go Back Previous
                            Menu::addSpace();
                            if (Menu::option == -1) {
                                goto AdminMenu;    // Exit to Admin Menu
                            } else {
                                if (selectNewStationLocationOpt == 3)
                                    goto AdminSelectLocationPage;    // Go Back to Select Location
                                else
                                    continue;        // Go Back to Select New Station Location
                            }
                        } else    // if admin hit 0 (Go Back Previous -> abort) during Enter {New Station}'s Sightseeing Spots -> SECOND: Enter Each Location
                            continue;    // Go Back to Select New Station Location
                    }
                }



                    // 3. Modify Subway Station Information
                else if (Menu::option == 3) {
                    while (true) {
                        // Select An Information To Modify
                        Menu::addHeader("Select An Information To Modify", "Go Back");
                        cout << "1. Station Name" << endl;
                        cout << "2. Travel Fare" << endl;
                        cout << "3. Travel Time" << endl;
                        Menu::recordAndValidateOption(0, 3);
                        Menu::addSpace();
                        // Check Select An Information To Modify Option
                        if (Menu::option == 0)        // Go Back to Admin Menu
                            break;

                        int selectAnInformationToModifyOpt = Menu::option;

                        while (true) {
                            if (selectAnInformationToModifyOpt == 1) {    // Modify 1. Station Name
                                // Select A Station
                                Menu::addHeader("Select A Station", "Go Back");
                                lst.showForward(7);
                                Menu::recordAndValidateOption(0, lst.getSize());
                            } else {                        // Modify 2. Travel Fare || 3. Travel Information
                                // Select A Route
                                Menu::addHeader("Select A Route", "Go Back");
                                Menu::addSubHeader("Between");
                                lst.showForwardEachNodeAndItsNextNode();
                                Menu::recordAndValidateOption(0, lst.getSize() -
                                                                 1);    // -1 becasue for e.g, 7 routes from 8 stations
                            }

                            Menu::addSpace();
                            // Check Select A Station Option	(Modify 1. Station Name)
                            // OR
                            // Check Select A Route Option		(Modify 2. Travel Fare || 3. Travel Information)
                            if (Menu::option == 0)        // Go Back to Select An Information To Modify
                                break;

                            string tempUserInput, newStationName;
                            double newTravelFare, newTravelTime;
                            bool goBack = false;
                            if (selectAnInformationToModifyOpt == 1) {        // Modify 1. Station Name
                                // Current Station Information
                                Menu::addHeader("Current Station Information", "Go Back");
                                cout << "-> Original Name\t: " +
                                        lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName << endl;
                                while (true) {
                                    cout << "-> New Name\t\t: ";
                                    // read user_input as string including whitespaces
                                    getline(cin, tempUserInput);
                                    // 0, Go Back Previous -> user abort
                                    if (Menu::isStringPureZero(tempUserInput)) {
                                        goBack = true;
                                        Menu::addSpace();
                                        break;    // Go Back to Select A Station
                                    }
                                    // only allow string with alphabets and either one space or hyphen between
                                    if (!Menu::isValidString(tempUserInput)) {
                                        Menu::showErrorMsg("Invalid station name");
                                        continue;
                                    }
                                    // assume New Station Name cannot be alphabet and > 15 characters
                                    if (tempUserInput.length() < 2 || tempUserInput.length() > 15) {
                                        Menu::showErrorMsg("Invalid station name (must be 2-15 characters)");
                                        continue;
                                    }
                                    // catch used Station Name from doubly linked list
                                    if (isTaken(tempUserInput, lst, &Subway::currentStationName)) {
                                        Menu::showErrorMsg("Station Name taken");
                                        continue;
                                    }
                                    // ! verified New Station Name
                                    newStationName = tempUserInput;
                                    // message to notify admin user
                                    cout << "\nCONGRATS. STATION NAME MODIFIED!" << endl;
                                    // update the doubly linked list accordingly
                                    lst.updateNodeData(Menu::option - 1, &Subway::currentStationName, newStationName);
                                    if (Menu::option - 1 ==
                                        0)                            // Modify First Station's Name		-> update following's station previousStationName
                                        lst.updateNodeData(Menu::option, &Subway::previousStationName, newStationName);
                                    else if (Menu::option - 1 == lst.getSize() -
                                                                 1)        // Modify Last Station's Name		-> update preceeding's station nextStationName
                                        lst.updateNodeData(Menu::option - 2, &Subway::nextStationName, newStationName);
                                    else {                                                // Modify In Between Stations' Name	-> update both of the above
                                        lst.updateNodeData(Menu::option, &Subway::previousStationName, newStationName);
                                        lst.updateNodeData(Menu::option - 2, &Subway::nextStationName, newStationName);
                                    }
                                    break;
                                }
                            } else {                                            // Modify 2. Travel Fare || 3. Travel Information
                                // Current Travel Information
                                Menu::addHeader("Current Travel Information", "Go Back");
                                Menu::addSubHeader(lst.getNodeAtIndex(Menu::option - 1)->data.currentStationName
                                                   + " -> " +
                                                   lst.getNodeAtIndex(Menu::option - 1)->data.nextStationName);

                                if (selectAnInformationToModifyOpt == 2) {    // Modify 2. Travel Fare
                                    cout << setprecision(2) << fixed;    // show two d.p
                                    cout << "-> Original Fare\t(RM) : "
                                         << lst.getNodeAtIndex(Menu::option - 1)->data.travelFareBetweenNextStation
                                         << endl;
                                    cout.precision(ss);                    // resets to system's default precision
                                    while (true) {
                                        cout << "-> New Fare\t\t(RM) : ";
                                        // read user_input as string including whitespaces
                                        getline(cin, tempUserInput);
                                        // 0, Go Back Previous -> user abort
                                        if (Menu::isStringPureZero(tempUserInput)) {
                                            goBack = true;
                                            Menu::addSpace();
                                            break;    // Go Back to Select A Route
                                        }
                                        // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
                                        if (!Menu::isDouble(tempUserInput)) {
                                            Menu::showErrorMsg("Invalid input");
                                            continue;
                                        }
                                        // convert user input to double
                                        newTravelFare = stod(tempUserInput);
                                        // assume New Travel Fare can be only 1-9999, catch out of range values
                                        if (!Menu::isInBetween(0.1, 9999.0, newTravelFare)) {
                                            Menu::showErrorMsg("Fare out of range (0.1-9999 only)");
                                            continue;
                                        }
                                        // ! verified New Travel Fare
                                        // message to notify admin user
                                        cout << "\nCONGRATS. TRAVEL FARE MODIFIED!" << endl;
                                        // update the doubly linked list
                                        // For e.g, Titiwangsa - PWTC affects two travel fares, next and previous
                                        lst.updateNodeData(Menu::option - 1, &Subway::travelFareBetweenNextStation,
                                                           newTravelFare);    // update Titiwangsa's nextTravelFare
                                        lst.updateNodeData(Menu::option, &Subway::travelFareBetweenPreviousStation,
                                                           newTravelFare);    // update PWTC's previousTravelFare
                                        break;
                                    }
                                } else {                                        // Modify 3. Travel Information
                                    cout << setprecision(1) << fixed;    // show two d.p
                                    cout << "-> Original Time\t(mins) : "
                                         << lst.getNodeAtIndex(Menu::option - 1)->data.travelTimeBetweenNextStation
                                         << endl;
                                    cout.precision(ss);                    // resets to system's default precision
                                    while (true) {
                                        cout << "-> New Time\t\t(mins) : ";
                                        // read user_input as string including whitespaces
                                        getline(cin, tempUserInput);
                                        // 0, Go Back Previous -> user abort
                                        if (Menu::isStringPureZero(tempUserInput)) {
                                            goBack = true;
                                            Menu::addSpace();
                                            break;    // Go Back to Select A Route
                                        }
                                        // catch string with alphanumeric, whitespace and special characters, except '-' in the beginning or '.' after first digit
                                        if (!Menu::isDouble(tempUserInput)) {
                                            Menu::showErrorMsg("Invalid input");
                                            continue;
                                        }
                                        // convert user input to double
                                        newTravelTime = stod(tempUserInput);
                                        // assume New Travel Time can be only 0.1-9999, catch out of range values
                                        if (!Menu::isInBetween(0.1, 9999.0, newTravelTime)) {
                                            Menu::showErrorMsg("Fare out of range (0.1-9999 only)");
                                            continue;
                                        }
                                        // ! verified New Travel Time
                                        // message to notify admin user
                                        cout << "\nCONGRATS. TRAVEL TIME MODIFIED!" << endl;
                                        // update the doubly linked list
                                        // For e.g, Titiwangsa - PWTC affects two travel times, next and previous
                                        lst.updateNodeData(Menu::option - 1, &Subway::travelTimeBetweenNextStation,
                                                           newTravelTime);    // update Titiwangsa's nextTravelTime
                                        lst.updateNodeData(Menu::option, &Subway::travelTimeBetweenPreviousStation,
                                                           newTravelTime);    // update PWTC's previousTravelTime
                                        break;
                                    }
                                }
                            }
                            if (!goBack) {
                                // Check Option For Final Menu (Current Station Information Or Current Travel Information)
                                Menu::addExitMenu("Admin Menu");
                                Menu::recordAndValidateOption(-1, 0);    // -1 Exit, 0 Go Back Previous
                                Menu::addSpace();
                                if (Menu::option == -1)
                                    goto AdminMenu;        // Exit to Admin Menu
                                else
                                    continue;            // Go Back to Select A Station Or Select A Route
                            } else
                                continue;
                        }
                    }
                }



                    // Amine and/or Shaun continue here
                    // 4. View All Ticket Purchases
                else if (Menu::option == 4) {
                    while (true) {
                        //Views all purchases and has an option to Delete a transaction
                        Menu::addHeader("All Ticket Purchase History", "Delete a Transaction");
                        Menu::addSubHeader(
                                "Transaction ID \tTicketID \tSource Station \tDestination \tTicket Amount \tDeparture Time \tCustomer ID \tCustomer Name \tCustomer IC \t\tTransaction Date and Time");
                        cout << setprecision(2) << fixed;
                        //Sorts the list by the transaction ID and displays all
                        TLL.sortByTransID();
                        TLL.show();
                        cout.precision(ss);
                        Menu::addExitMenu("Admin Menu");
                        Menu::recordAndValidateOption(-1, 0);
                        //Admin selects to either delete a transaction or go back to the menu
                        if (Menu::option == -1) {
                            Menu::addSpace();
                            goto AdminMenu;
                        } else if (Menu::option == 0) {
                            //Customer enters the Transaction ID to be deleted or can select to cancel deletion
                            cout << endl << "Enter Transaction ID to be Delete or 0 to cancel: ";
                            string TransID;
                            int index;
                            getline(cin, TransID);
                            if (TransID == "0") {
                                Menu::addSpace();
                                goto AdminMenu;
                            } else {
                                index = TLL.getIndex(TransID);//Checks for the index of the transaction ID
                                if (index == -1) { // If the Transaction ID is not found
                                    Menu::showErrorMsg("Transaction Does Not Exist");
                                    continue;
                                } else {
                                    TLL.deleteAt(index); // Deletes the Transaction ID
                                    cout << endl << "Transaction Deleted";
                                }
                                Menu::addExitMenu("Admin Menu");
                                Menu::recordAndValidateOption(-1, 0);
                                Menu::addSpace();
                                break;
                            }
                        }
                        break;
                    }
                }

                    //5. Sort Ticket Purchase According To Passenger Name
                else if (Menu::option == 5) {
                    while (true) {
                        //Allows the admin to go back to menu if selected 0
                        Menu::addHeader("View Transactions based on Passenger Name", "Go back to Admin Menu");
                        Menu::addSubHeader(
                                "Transaction ID \tTicketID \tSource Station \tDestination \tTicket Amount \tDeparture Time \tCustomer ID \tCustomer Name \tCustomer IC \t\tTransaction Date and Time");
                        cout << setprecision(2) << fixed;
                        TLL.sortNameAsc(); //Calls to sort the List in ascending order of Names
                        TLL.show(); //Displays the list
                        Menu::addExitMenu("Admin Menu");
                        Menu::recordAndValidateOption(-1, 0);
                        Menu::addSpace();
                        break;
                    }
                }

                    //6. Search Customer Ticket Purchase
                else if (Menu::option == 6) {
                    while (true) {
                        Menu::addHeader("View Specific Customer Transactions", "Go back to Admin Menu");
                        cout << "Enter Customer ID: ";
                        string ID;
                        getline(cin, ID);
                        Menu::addSubHeader(
                        		"Transaction ID \tTicketID \tSource Station \tDestination \tTicket Amount \tDeparture Time \tCustomer ID \tCustomer Name \tCustomer IC \t\tTransaction Date and Time");
                        int CusID = stoi(ID);
                        if (CusID == 0) {//Will go back to Admin menu if 0 is entered
                            break;
                        } else {
                        	cout << setprecision(2) << fixed;
                            TLL.showByCusID(CusID);//Displays the Ticket purchases of specific customer
                            Menu::addExitMenu("Admin Menu");
                            Menu::recordAndValidateOption(-1, 0);
                            Menu::addSpace();
                            break;
                        }
                    }
                }

                    //7. Modify Customer Ticket Purchase
                else if (Menu::option == 7) {
                    while (true) {
                        //First will show admin all purchases
                        Menu::addHeader("All Purchase History", "Modify a Transaction");
                        Menu::addSubHeader(
                                "Transaction ID \tTicketID \tSource Station \tDestination \tTicket Amount \tDeparture Time \tCustomer ID \tCustomer Name \tCustomer IC \t\tTransaction Date and Time");
                        cout << setprecision(2) << fixed;
                        TLL.sortByTransID();
                        TLL.show();
                        cout.precision(ss);
                        Menu::addExitMenu("Admin Menu");
                        Menu::recordAndValidateOption(-1, 0); //Gives admin option to modify or go back
                        if (Menu::option == 0) {
                            //Admin can select to cancel of enter transaction ID to modify
                            cout << endl << "Enter Transaction ID to be Delete or 0 to cancel: ";
                            string TransID;
                            getline(cin, TransID);
                            //Check if the transaction exists
                            if (TLL.getIndex(TransID) == -1) {
                                cerr << "Transaction not Found" << endl;
                                continue;
                            } else {
                                // Select Start And End Stations
                                int startStationOpt, endStationOpt;
                                Menu::addHeader("Select Start And End Stations", "Go Back");
                                lst.showForward(7);
                                // Check Select Start And End Stations Option
                                Menu::recordAndValidateOption(0, lst.getSize(), "Start Station");
                                if (Menu::option ==
                                    0) {        // Enter Start Station: 0, means want to Go Back to Customer Menu
                                    Menu::addSpace();
                                    break;
                                } else
                                    startStationOpt = Menu::option;
                                CustomerSelectEndStationMod:
                                Menu::recordAndValidateOption(0, lst.getSize(), "End Station");
                                if (Menu::option ==
                                    0) {        // Enter End Station: 0, means want to Go Back to Customer Menu
                                    Menu::addSpace();
                                    break;
                                }
                                    // catch SAME Start and End Stations
                                else if (Menu::option == startStationOpt) {
                                    cerr << ("To-And-From Same Station? Try Again") << endl;
                                    Sleep(100);
                                    goto CustomerSelectEndStationMod;
                                } else
                                    endStationOpt = Menu::option;
                                Menu::addSpace();

                                //Calculating the Departure time for the ticket
                                time_t now = time(0);
                                tm *ltm = localtime(&now);
                                int Hour = ltm->tm_hour;
                                int Min = ltm->tm_min;
                                if (Min > 30) {
                                    Min = Min - (Min - 30);
                                } else {
                                    Min = Min - Min;
                                }
                                //If it is reversed
                                if ((endStationOpt - 1) < (startStationOpt - 1)) {
                                    Min = Min +
                                          lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, lst.getSize(), 3);
                                } else {
                                    Min = Min + lst.getDataDifferenceBetweenTwoNodes(0, startStationOpt - 1, 3);
                                }
                                if (Min < ltm->tm_min) {
                                    Min = Min + 30;
                                }
                                if (Min > 60) {
                                    Min = Min - 60;
                                    Hour = Hour + 1;
                                }
                                string Dtime = to_string(Hour) + ":" + to_string(Min);
                                //Calling the modify function to modify the ticket
                                TLL.Modify(TransID, lst.getNodeAtIndex(startStationOpt - 1)->data.currentStationName,
                                           lst.getNodeAtIndex(endStationOpt - 1)->data.currentStationName,
                                           lst.getDataDifferenceBetweenTwoNodes(startStationOpt - 1, endStationOpt - 1,
                                                                                2), Dtime);
                                Menu::addExitMenu("Admin Menu");
                                Menu::recordAndValidateOption(-1, 0);
                                Menu::addSpace();
                            }
                        } else {
                            break;
                        }
                    }
                }

                    //8. Flushing Queue and LL
                else if (Menu::option == 8) {
                    while (true) {
                        if (q.size() > 0) {
                            string TDateTime = q.getHead().getTransDT();
                            string year = TDateTime.substr(TDateTime.size() - 5);
                            time_t now = time(0);
                            tm *ltm = localtime(&now);
                            int cyear = 1900 + ltm->tm_year;
                            if (stoi(year) < cyear) {
                                string tid = q.getHead().getTrID();
                                q.dequeue();
                                int index = TLL.getIndex(tid);
                                TLL.deleteAt(index);
                            } else {
                                cout << "Flushed all year old transactions" << endl;
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                }

                while (Menu::option == 9) {
                    user = {};
                    User tempUser;
                    Admin tempAdmin;
                    string userInput, tempUsername, tempEmail, tempIc;

//                Username, Email, Ic
                    while (true) {
//                    Enter username
                        Menu::addHeader("Admin Registration Menu", "Go Back");
                        cout << "Enter username: ";

                        getline(cin, tempUsername);

                        if (Menu::isStringOrZero(tempUsername)) {
                            Menu::option = 0;
                            Menu::addSpace();
                            break;
                        }

//                    Enter email
                        cout << endl;
                        cout << "Enter email: ";

                        getline(cin, tempEmail);

                        if (Menu::isStringOrZero(tempUsername)) {
                            Menu::option = 0;
                            Menu::addSpace();
                            break;
                        }

//                    Enter ic
                        cout << endl;
                        cout << "Enter ic: ";

                        getline(cin, tempIc);

                        if (Menu::isStringOrZero(tempUsername)) {
                            Menu::option = 0;
                            Menu::addSpace();
                            break;
                        }

//                    Username, Email, Ic validation
                        if (!User::isValidUsername(tempUsername)) {
                            Menu::showErrorMsg("Invalid username");
                            Menu::addSpace();
                            continue;
                        } else if (!User::isValidEmail(tempEmail)) {
                            Menu::showErrorMsg("Invalid email");
                            Menu::addSpace();
                            continue;
                        } else if (!User::isValidIc(tempIc)) {
                            Menu::showErrorMsg("Invalid ic");
                            Menu::addSpace();
                            continue;
                        }

//                    Check if records already exist
                        tempUser = userLst.getByUsername(tempUsername);
                        if (!tempUser.username.empty()) {
                            Menu::showErrorMsg("Username already exists");
                            Menu::addSpace();
                            continue;
                        }
                        tempUser = userLst.getByEmail(tempEmail);
                        cout << tempUser.email << endl;
                        if (!tempUser.email.empty()) {
                            Menu::showErrorMsg("Email is in use");
                            Menu::addSpace();
                            continue;
                        }
                        tempUser = userLst.getByIc(tempIc);
                        if (!tempUser.ic.empty()) {
                            Menu::showErrorMsg("Ic is in use");
                            Menu::addSpace();
                            continue;
                        }

                        tempAdmin.username = tempUsername;
                        tempAdmin.email = tempEmail;
                        tempAdmin.ic = tempIc;
                        Menu::addSpace();
                        break;
                    }

//                Password validation
                    while (!tempAdmin.username.empty()) {
                        string tempPassword;
                        Menu::addHeader("Admin Registration Menu", "Go Back");
                        cout << "Enter password: ";
                        getline(cin, userInput);

                        if (Menu::isStringOrZero(userInput)) {
                            Menu::option = 0;
                            Menu::addSpace();
                            break;
                        }

                        if (!User::isValidPassword(userInput)) {
                            Menu::showErrorMsg("Invalid password");
                            Menu::addSpace();
                            continue;
                        }

                        tempPassword = userInput;
                        Menu::addSpace();

//                    Confirm password
                        while (true) {
                            Menu::addHeader("Admin Registration Menu", "Go Back");
                            cout << "Re-enter password: ";
                            getline(cin, userInput);

                            if (Menu::isStringOrZero(userInput)) {
                                Menu::option = 0;
                                Menu::addSpace();
                                break;
                            }

                            if (tempPassword == userInput) {
                                tempAdmin.password = tempPassword;
                                Menu::addSpace();
                                break;
                            }

                            Menu::showErrorMsg("Passwords do not match");
                            Menu::addSpace();
                        }

                        if (Menu::option == 0 && (tempPassword == "" | tempPassword.empty())) {
                            break;
                        }
                        else if (Menu::option == 0) continue;

                        tempAdmin.password = tempPassword;
                        break;
                    }

                    if (!tempAdmin.password.empty()) {
//                    generate new id
                        tempAdmin.id = (userLst.getLast().id + 1);

                        Admin newAdmin = Admin(tempAdmin.id, tempAdmin.username, tempAdmin.password, tempAdmin.ic, tempAdmin.email);
                        userLst.insertLast(newAdmin);
                        Menu::showNotification("Account was registered successfully");
                        Menu::addSpace();
                        break;
                    }

                    if ((Menu::option == 0) | !tempAdmin.password.empty()) {
                        Menu::addSpace();
                        break;
                    }
                }

                if (Menu::option == 10) {
                    while (true) {
                        string userInput;
                        User tempUser;
                        int userIndex;

                        Menu::addHeader("Edit Personal Details", "Go Back");
                        cout << "1. Change username" << endl;
                        cout << "2. Change password" << endl;
                        cout << "3. Change ic" << endl;
                        cout << "4. Change email" << endl;
                        Menu::recordAndValidateOption(0, 4);
                        Menu::addSpace();

                        if (Menu::option == 0) { break; }

                        while (Menu::option <= 4 | Menu::option >= 1) {
                            if (Menu::option == 1) {
                                Menu::addHeader("Edit Personal Details - Change Username", "Go Back");
                                cout << "Username: " << user.username << endl;
                                cout << "Change to: ";
                            }
                            else if (Menu::option == 2) {
                                Menu::addHeader("Edit Personal Details - Change password", "Go Back");
                                cout << "Password: " << user.password << endl;
                                cout << "Change to: ";
                            }
                            else if (Menu::option == 3) {
                                Menu::addHeader("Edit Personal Details - Change ic", "Go Back");
                                cout << "Ic: " << user.ic << endl;
                                cout << "Change to: ";
                            }
                            else if (Menu::option == 4) {
                                Menu::addHeader("Edit Personal Details - Change email", "Go Back");
                                cout << "Email: " << user.email << endl;
                                cout << "Change to: ";
                            }

                            getline(cin, userInput);

                            if (Menu::isStringOrZero(userInput)) {
                                Menu::option = 0;
                                Menu::addSpace();
                                break;
                            }

                            if (Menu::option == 1 && !User::isValidUsername(userInput)) {
                                Menu::showErrorMsg("Invalid username");
                                Menu::addSpace();
                                continue;
                            }
                            else if (Menu::option == 2 && !User::isValidPassword(userInput)) {
                                Menu::showErrorMsg("Invalid password");
                                Menu::addSpace();
                                continue;
                            }
                            else if (Menu::option == 3 && !User::isValidIc(userInput)) {
                                Menu::showErrorMsg("Invalid ic");
                                Menu::addSpace();
                                continue;
                            }
                            else if (Menu::option == 4 && !User::isValidEmail(userInput)) {
                                Menu::showErrorMsg("Invalid email");
                                Menu::addSpace();
                                continue;
                            }


                            if (Menu::option == 1) {
                                tempUser = userLst.getByUsername(userInput);
                                if (!tempUser.username.empty()) {
                                    Menu::showErrorMsg("Username already exists");
                                    Menu::addSpace();
                                    continue;
                                }

                                user.username = userInput;
                            }
                            else if (Menu::option == 2) {
                                user.password = userInput;
                            }
                            else if (Menu::option == 3) {
                                tempUser = userLst.getByIc(userInput);
                                if (!tempUser.ic.empty()) {
                                    Menu::showErrorMsg("Ic is in use");
                                    Menu::addSpace();
                                    continue;
                                }

                                user.ic = userInput;
                            }
                            else if (Menu::option == 4) {
                                tempUser = userLst.getByEmail(userInput);
                                if (!tempUser.email.empty()) {
                                    Menu::showErrorMsg("Email is in use");
                                    Menu::addSpace();
                                    continue;
                                }

                                user.email = userInput;
                            }

                            bool isModified = userLst.modify(user);
                            if (isModified) {
                                Menu::showNotification("Details have been updated");
                                Menu::addSpace();
                                break;
                            }
                            else {
                                Menu::showErrorMsg("User not found");
                                Menu::addSpace();
                                continue;
                            }
                        }
                    }
                }
            }

            user = {};
        }
    }

	catch (const invalid_argument& e)
	{
		cerr << e.what()<< endl;
	}
	return 0;
}




