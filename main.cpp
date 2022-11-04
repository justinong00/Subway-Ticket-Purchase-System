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
        User user;
        LinkedList<User> userLst;
        userLst.insertLast(Customer(1, "johndoe", "johndoe123", "1234", "johndoe@gmail.com"));
        userLst.insertLast(Admin(2, "janedoe", "janedoe123", "2345"));
        userLst.show();

        while (true) {
            MainMenu:
            Menu::showMainMenu();
            if (Menu::option == 0) break;

            Menu::addSpace();

//            Login
            while (Menu::option == 1) {
                boolean usernameIsValid = false;
                boolean passwordIsValid = false;
                string userInput;
                User tempUser;

//                Username validation
                while (true) {
                    Menu::addHeader("Login Menu", "Go Back");
                    cout << "Enter username: ";

                    getline(cin, userInput);

                    if (Menu::isInteger(userInput) && stoi(userInput) == 0) {
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

                    if (Menu::isInteger(userInput) && stoi(userInput) == 0) {
                        Menu::option = 0;
                        Menu::addSpace();
                        break;
                    }

                    if (userInput != tempUser.password) {
                        Menu::showErrorMsg("Incorrect password");
                        Menu::addSpace();
                        continue;
                    }

                    passwordIsValid = true;
                    user = tempUser;
                    break;
                }

                if ((Menu::option == 0) | passwordIsValid) break;
            }

//            Customer Registration
            while (Menu::option == 2 && user.username.empty()) {
                User tempUser;
                string userInput;

                while (true) {
                    Menu::addHeader("Registration Menu", "Go Back");
                    cout << "Enter username: ";

                    getline(cin, userInput);

                    if (Menu::isInteger(userInput) && stoi(userInput) == 0) {
                        Menu::option = 0;
                        Menu::addSpace();
                        break;
                    }

                    if (Menu::isValidUsername(userInput) && !Menu::isInteger(userInput)) {
                        tempUser.username = userInput;
                        cout << "valid username" << endl;
                        break;
                    }

                    Menu::showErrorMsg("Invalid username");
                    Menu::addSpace();
                    continue;
                }

                while (!tempUser.username.empty()){

                }

                if (Menu::option == 0) break;
            }

            if (!user.username.empty()) {
                Menu::addSpace();
                break;
            }
        }


    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
}