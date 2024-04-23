#include "People.h"
#include "customInput.h"
#include "DatabaseManager.h"
#include "Password.h"

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
    std::cout << "\n\t\t\t\tEnter username:";
    takeInput(&username);
    // Check if username already exists in the database
    DatabaseManager dbManager;
    if (dbManager.isUsernameExists(username)) {
        std::cout << "\n\t\t\t\tUsername already exists! Please choose another username.\n" << std::endl;
        return false;
    }

    //If username is unique, create the account
    std::cout << "\t\t\t\tEnter first name:";
    takeInput(&firstName,false);
    std::cout << "\t\t\t\tEnter last name:";
    takeInput(&lastName,false);
    std::cout << "\t\t\t\tEnter Date of Birth:";
    takeInput(&dob);
    std::cout << "\t\t\t\tEnter password:";
    Password _pass;
    _pass.getPasswordFromUser();
    password = _pass.getEncryptedPassword();
    std::cout << "\t\t\t\tEnter secret answer to recover password if you forget it:";
    takeInput(&secretAnswer);
    return true;
}

bool People::login() {
    std::string _username;Password _password;
    std::cout << "\t\t\t\tEnter username:";
    takeInput(&_username);
    std::cout << "\t\t\t\tEnter password:";
    _password.getPasswordFromUser();

    // Check if the username and password match in the database
    DatabaseManager dbManager;
    if (dbManager.verifyUser(_username, _password.getEncryptedPassword())) {
        setUsername(_username);
        std::cout << "\n\t\t\t\tLogin successful!" << std::endl;
        return true;
    }
    else {
        std::cout << "\n\t\t\t\tLogin unsuccessful!" << std::endl;
        return false;
    }
}

size_t People::showDetails() {
    // Calculate the maximum length among all fields
    size_t maxFieldLength = std::max({ username.length(), firstName.length(), lastName.length(), dob.length(), password.length(), secretAnswer.length() });

    // Compare with a fixed value
    maxFieldLength = std::max(maxFieldLength, static_cast<size_t>(20));

    // Determine the width of each column
    size_t columnWidth = maxFieldLength + 4; // Add extra space for formatting

    // Output the table with uniform column widths
    std::cout << "\n\t\t\t\t\t\t\tUser Information\n" << std::endl;
    std::cout << "\t\t\t\t\t+--------------------+"<< std::string(columnWidth, '-') <<"+ " << std::endl;
    std::cout << "\t\t\t\t\t|     Field          |"<<"      Information" << std::string(columnWidth - 17, ' ') << "|" << std::endl;
    std::cout << "\t\t\t\t\t+--------------------+" << std::string(columnWidth, '-') << "+ " << std::endl;
    std::cout << "\t\t\t\t\t|     Username       |"<< username << std::string(columnWidth - username.length(), ' ') << "|" << std::endl;
    std::cout << "\t\t\t\t\t|     First name     |" << firstName << std::string(columnWidth - firstName.length(), ' ') << "|" << std::endl;
    std::cout << "\t\t\t\t\t|     Last name      |" << lastName << std::string(columnWidth - lastName.length(), ' ') << "|" << std::endl;
    std::cout << "\t\t\t\t\t|     Date of Birth  |" << dob << std::string(columnWidth - dob.length(), ' ') << "|" << std::endl;
    // Uncomment to print password
    //std::cout << "\t\t\t\t\t|     Password     |     " << password << std::string(columnWidth - password.length(), ' ') << "|" << std::endl;
    //std::cout << "\t\t\t\t\t|     Secret answer|     " << secretAnswer << std::string(columnWidth - secretAnswer.length(), ' ') << "|" << std::endl;
    //std::cout << "\t\t\t\t\t+------------------+" << std::string(columnWidth, '-') << "+ " << std::endl;
    return columnWidth;
}

bool People::changePassword() {
    Password oldPass;
    DatabaseManager dbManager;
    if (username == "") {
        std::cout << "\t\t\t\tEnter username: ";
        takeInput(&username);
    }
    std::cout << "\t\t\t\tEnter old password: ";
    oldPass.getPasswordFromUser();
    if (dbManager.verifyUser(username,oldPass.getEncryptedPassword())){
        Password newPass;
        std::cout << "\t\t\t\tEnter new password: ";
        newPass.getPasswordFromUser();
        if (dbManager.changePassword(username, newPass.getEncryptedPassword())) {
            setPassword(newPass.getEncryptedPassword());
            return true;
        }
    }
    return false;
}

bool People::forgotPassword() {
    std::string username, secret;
    DatabaseManager dbManager;
    std::cout << "\t\t\t\tEnter username: ";
    takeInput(&username);

    std::cout << "\t\t\t\tEnter secret: ";
    takeInput(&secret);
    
    if (dbManager.verifySecret(username, secret)) {
        setUsername(username);
        Password newPass;
        std::cout << "\t\t\t\tEnter new password: ";
        newPass.getPasswordFromUser();
        if(dbManager.changePassword(username, newPass.getEncryptedPassword()))
        {
            return true;
        }
    }
    return false;
}
