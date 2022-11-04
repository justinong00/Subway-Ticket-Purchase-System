//
// Created by chanw on 04/11/2022.
//

#include "menu.h"
#include "User.h"
#include "Admin.h"
#include "LinkedList.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int Menu::option = 0;

int main() {
    try {
        User user = {};
        LinkedList<User> userLst;
        userLst.insertLast(Customer(1, "johndoe", "johndoe123", "012345678901", "johndoe@gmail.com"));
        userLst.insertLast(Admin(2, "janedoe", "janedoe123", "123456789012", "janedoe@gmail.com"));

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
                    }
                    else if (!User::isValidEmail(tempEmail)) {
                        Menu::showErrorMsg("Invalid email");
                        Menu::addSpace();
                        continue;
                    }
                    else if (!User::isValidIc(tempIc)) {
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
                while (!newCustomer.username.empty()){
                    string tempPassword;
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

                    newCustomer.password = tempPassword;
                    break;
                }

//                generate new id
                newCustomer.id = (userLst.getLast().id + 1);

                user = Customer(newCustomer.id, newCustomer.username, newCustomer.password, newCustomer.ic, newCustomer.email);
                userLst.insertLast(user);
                cout << user.role.toString() << endl;
                if ((Menu::option == 0) | !user.username.empty()) {
                    Menu::addSpace();
                    break;
                }
            }

            CustomerMenu:
            while (user.role.isCustomer()) {
                Menu::showCustomerMenu();
                Menu::addSpace();
                if (Menu::option == 0) {break;}

            }

            AdminMenu:
            while (user.role.isAdmin()) {
                Menu::showAdminMenu();
                Menu::addSpace();
                if (Menu::option == 0) {break;}
            }
        }


    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
}