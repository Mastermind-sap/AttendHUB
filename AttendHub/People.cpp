#include "People.h"
#include "customInput.h"

People::People(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer)
    : firstName(_firstName), lastName(_lastName), dob(_dob), username(_username), password(_password), secretAnswer(_secretAnswer) {}

bool People::signup() {
    std::cout << "Enter username:";
    takeInput(&username);
    if ("sap" == username) {
        std::cout << "Username already exists! Please choose another username." << std::endl;
        return false;
    }

    //If username is unique, create the account
    std::cout << "Enter first name:";
    takeInput(&firstName);
    std::cout << "Enter last name:";
    takeInput(&lastName);
    std::cout << "Enter Date of Birth:";
    takeInput(&dob);
    std::cout << "Enter password:";
    takeInput(&password);
    std::cout << "Enter secret answer to recover password if you forget it:";
    takeInput(&secretAnswer);

    std::cout << "Account created successfully!" << std::endl;
    return true;
}

bool People::login(const std::string& _username, const std::string& _password) {
    if (username == _username && password == _password) {
        std::cout << "Login successful!" << std::endl;
        return true;
    }
    else {
        std::cout << "Login unsuccessful!" << std::endl;
        return false;
    }
}

void People::showDetails() {
    std::cout << "Username:" << username << std::endl;
    std::cout << "First name:"<<firstName << std::endl;
    std::cout << "Last name:" << lastName << std::endl;
    std::cout << "Date of Birth:" << dob << std::endl;
    std::cout << "Password:" << password << std::endl;
    std::cout << "Secret answer:" << secretAnswer << std::endl;
}

void People::changePassword(const std::string& _username, const std::string& oldPass, const std::string& newPass) {
    if (username == _username && password == oldPass) {
        password = newPass;
        std::cout << "Password changed successfully!" << std::endl;
    }
    else {
        std::cout << "Incorrect username or password!" << std::endl;
    }
}

void People::forgotPassword(const std::string& _username, const std::string& _secretAnswer) {
    if (username == _username && secretAnswer == _secretAnswer) {
        std::cout << "Your password is: " << password << std::endl;
    }
    else {
        std::cout << "Incorrect username or secret answer!" << std::endl;
    }
}
