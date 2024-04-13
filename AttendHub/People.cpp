#include "People.h"
#include "customInput.h"
#include "DatabaseManager.h"

People::People(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer)
    : firstName(_firstName), lastName(_lastName), dob(_dob), username(_username), password(_password), secretAnswer(_secretAnswer) {}



// Getter methods
std::string People::getFirstName() const { return firstName; }
std::string People::getLastName() const { return lastName; }
std::string People::getDOB() const { return dob; }
std::string People::getUsername() const { return username; }
std::string People::getPassword() const { return password; }
std::string People::getSecretAnswer() const { return secretAnswer; }


// Setter methods
void People::setFirstName(const std::string& _firstName) { firstName = _firstName; }
void People::setLastName(const std::string& _lastName) { lastName = _lastName; }
void People::setDOB(const std::string& _dob) { dob = _dob; }
void People::setUsername(const std::string& _username) { username = _username; }
void People::setPassword(const std::string& _password) { password = _password; }
void People::setSecretAnswer(const std::string& _secretAnswer) { secretAnswer = _secretAnswer; }


bool People::signup() {
    std::cout << "Enter username:";
    takeInput(&username);
    // Check if username already exists in the database
    DatabaseManager dbManager;
    if (dbManager.isUsernameExists(username)) {
        std::cout << "Username already exists! Please choose another username." << std::endl;
        return false;
    }

    //If username is unique, create the account
    std::cout << "Enter first name:";
    takeInput(&firstName,false);
    std::cout << "Enter last name:";
    takeInput(&lastName,false);
    std::cout << "Enter Date of Birth:";
    takeInput(&dob);
    std::cout << "Enter password:";
    takeInput(&password);
    std::cout << "Enter secret answer to recover password if you forget it:";
    takeInput(&secretAnswer);
    return true;
}

bool People::login() {
    std::string _username, _password;
    std::cout << "Enter username:";
    takeInput(&_username);
    std::cout << "Enter password:";
    takeInput(&_password);
    // Check if the username and password match in the database
    DatabaseManager dbManager;
    if (dbManager.verifyUser(_username, _password)) {
        setUsername(_username);
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
