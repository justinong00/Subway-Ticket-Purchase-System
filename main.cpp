//
// Created by chanw on 04/11/2022.
//

#include "menu.h"
#include "User.h"
#include "Admin.h"
#include "LinkedList.h"
#include "PreLoginMenu.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int Menu::option = 0;

int main() {
    try {
        LinkedList<User> adminLst;
        adminLst.insertLast(Customer(1, "johndoe", "johndoe123", "1234", "johndoe@gmail.com"));
        adminLst.insertLast(Admin(2, "janedoe", "janedoe123", "2345"));
        adminLst.show();


        MainMenu:
        PreLoginMenu::showMainMenu();
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }
}