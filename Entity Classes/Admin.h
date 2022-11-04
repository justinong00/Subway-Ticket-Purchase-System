//
// Created by chanw on 04/11/2022.
//

#include "User.h"

#ifndef DSTR_ASSIGNMENT_ADMIN_H
#define DSTR_ASSIGNMENT_ADMIN_H

using namespace std;

class Admin: public User {
public:

    Admin() = default;

    Admin(int id, string username, string password, string ic) : User(id, username, password, ic){
        this->role = UserType::AdminType;
    };

    void registerAdmin()
    {

    }
};

#endif //DSTR_ASSIGNMENT_ADMIN_H
