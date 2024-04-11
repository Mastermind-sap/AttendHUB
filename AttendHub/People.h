//#pragma once
#ifndef PEOPLE_H
#define PEOPLE_H

#include <iostream>
#include <string>

class People {
protected:
    std::string firstName;
    std::string lastName;
    std::string dob;
    std::string username;
    std::string password;
    std::string secretAnswer;

public:
    // Default constructor
    People() : firstName(""), lastName(""), dob(""), username(""), password(""), secretAnswer("") {}

    // Parameterized constructor
    People(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer);
    virtual ~People() {}
    
    virtual bool signup();
    virtual bool login(const std::string& _username, const std::string& _password);
    void showDetails();
    void changePassword(const std::string& _username, const std::string& oldPass, const std::string& newPass);
    void forgotPassword(const std::string& _username, const std::string& _secretAnswer);
};

#endif
