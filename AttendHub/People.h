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

    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getDOB() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getSecretAnswer() const;

    // Setters
    void setFirstName(const std::string& _firstName); 
    void setLastName(const std::string& _lastName);
    void setDOB(const std::string& _dob);
    void setUsername(const std::string& _username);
    void setPassword(const std::string& _password);
    void setSecretAnswer(const std::string& _secretAnswer);
    
    virtual bool signup();
    virtual bool login();
    void showDetails();
    void changePassword(const std::string& _username, const std::string& oldPass, const std::string& newPass);
    void forgotPassword(const std::string& _username, const std::string& _secretAnswer);
};

#endif
