//
// Created by chanw on 04/11/2022.
//

#ifndef DSTR_ASSIGNMENT_USER_H
#define DSTR_ASSIGNMENT_USER_H

#include <string>
#include <iostream>
#include "PreLoginMenu.h"

using namespace std;

class UserType {
public:
    UserType(nullptr_t pVoid) {}

    enum Value {
        AdminType,
        CustomerType
    };

    UserType() = default;
    constexpr UserType(Value aUserType) : value(aUserType) {}

    string toString()
    {
        switch (value) {
            case 0:
                return "AdminType";
            case 1:
                return "CustomerType";
        }
    }

private:
    Value value;
};

class User {
public:
    int id;
    string username, password, ic;
    UserType role;

    User() = default;

    User(int id, string username, string password, string ic)
    {
        this->id = id;
        this->username = username;
        this->password = password;
        this->ic = ic;
    }

    void login(string username, string password)
    {

    }

    void registerCustomer(string username, string password)
    {

    }
};

#endif //DSTR_ASSIGNMENT_USER_H
