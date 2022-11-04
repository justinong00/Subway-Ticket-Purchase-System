//
// Created by chanw on 04/11/2022.
//

#ifndef DSTR_ASSIGNMENT_PRELOGINMENU_H
#define DSTR_ASSIGNMENT_PRELOGINMENU_H

#include "menu.h"

class PreLoginMenu: public Menu {

public:


    static void showRegistrationMenu() {
        addHeader("Registration Menu", "Back");
//        TODO: receive inputs, validate inputs, call register() from User.h
    }


};

#endif //DSTR_ASSIGNMENT_PRELOGINMENU_H
