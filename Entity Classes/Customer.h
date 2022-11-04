//
// Created by chanw on 04/11/2022.
//

#include "User.h"

#ifndef DSTR_ASSIGNMENT_CUSTOMER_H
#define DSTR_ASSIGNMENT_CUSTOMER_H

class Customer: public User {
public:
    string email;

    Customer() = default;

    Customer(int id, string username, string password, string ic, string email) : User(id, username, password, ic){
        this->email = email;
        this->role = UserType::CustomerType;
    }
};

#endif //DSTR_ASSIGNMENT_CUSTOMER_H
