#include "Menu.h"

#ifndef DSTR_ASSIGNMENT_USER_H
#define DSTR_ASSIGNMENT_USER_H

#include <string>
#include <iostream>

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

    bool isAdmin() {
        if (this->value == AdminType) return true;
        else return false;
    }

    bool isCustomer() {
        if (this->value == CustomerType) return true;
        else return false;
    }

private:
    Value value;
};

class User {
public:
    int id;
    string username, password, ic, email;
    UserType role;

    User() = default;

    User(int id, string username, string password, string ic, string email)
    {
        this->id = id;
        this->username = username;
        this->password = password;
        this->ic = ic;
        this->email = email;
    }

    static bool isValidUsername(string userInput) {
        const regex pattern("^[a-zA-Z0-9_]+$");
        if (Menu::isInteger(userInput)) {return false;}
        else {return regex_match(userInput, pattern);}
    }

    static bool isValidPassword(string userInput) {
        bool hasUpper = false;
        bool hasLower = false;
        bool hasSpecial = false;
        bool hasNumber = false;

        const regex pattern("^[a-zA-Z0-9_/|!?%^*]+$");
        const regex upper("[A-Z]+");
        const regex lower("[a-z]+");
        const regex special("[_/|!?%^*]+");
        const regex number("[0-9]+");

        hasUpper = regex_search(userInput, upper);
        hasLower = regex_search(userInput, lower);
        hasSpecial = regex_search(userInput, special);
        hasNumber = regex_search(userInput, number);

        int total = hasUpper + hasLower + hasSpecial + hasNumber;

        if (userInput.length() <= 8) {return false;}
        else if(!regex_match(userInput, pattern)) {return false;}
        if (total < 4) {return false;}
        else {return true;}
    }

    static bool isValidEmail(string userInput) {
        const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
        return regex_match(userInput, pattern);
    }

    static bool isValidIc(string userInput) {
        if ((userInput.length() == 12) && isInt(userInput)) {return true;}
        else return false;
    }

private:
    static bool isInt(string userInput) {
        const regex pattern("^[0-9]+$");
        return regex_match(userInput, pattern);
    }
};

#endif //DSTR_ASSIGNMENT_USER_H
