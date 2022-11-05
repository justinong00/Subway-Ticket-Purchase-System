//
// Created by chanw on 04/11/2022.
//

#include "User.h"

#ifndef DSTR_ASSIGNMENT_CUSTOMER_H
#define DSTR_ASSIGNMENT_CUSTOMER_H

class Customer: public User {
public:

    Customer() = default;

    Customer(int id, string username, string password, string ic, string email) : User(id, username, password, ic, email){
        this->role = UserType::CustomerType;
    }
};

#endif //DSTR_ASSIGNMENT_CUSTOMER_H
