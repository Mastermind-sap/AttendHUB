#include "Student.h"
#include "customInput.h"

Student::Student(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer, const std::string& _branch, char _section, const int& _yearOfPass, const int& _scholarID)
    : People(_firstName, _lastName, _dob, _username, _password, _secretAnswer), branch(_branch), section(_section), yearOfPass(_yearOfPass), scholarID(_scholarID) {}

bool Student::signup() {
    // Call the People::signup method to get common user details
    bool success = People::signup();
    if (success) {
        // Prompt for additional student details
        std::cout << "Enter branch: ";
        takeInput(&branch);

        std::cout << "Enter section: ";
        takeInput(&section);

        std::cout << "Enter year of passing: ";
        takeInput(&yearOfPass);

        std::cout << "Enter scholar ID: ";
        takeInput(&scholarID);

        std::cout << "Student account created successfully!" << std::endl;
        std::cout << "Signup Successfull!!\n";
        return true;
    }
    else {
        std::cout << "Signup Unsuccessfull!!\n";
        return false;
    }
}


bool Student::login() {
    return People::login();
}
void Student::viewSubjects()
{
}

void Student::addSubject()
{
}

void Student::deleteSubject()
{
}

void Student::addAttendance()
{
}

void Student::editAttendance()
{
}

void Student::viewAttendance() {
    // Implement view attendance for student
}

void Student::viewProfile() {
    // Display common user details using People::showDetails method
    People::showDetails();

    // Display student-specific details
    std::cout << "Branch: " << branch << std::endl;
    std::cout << "Section: " << section << std::endl;
    std::cout << "Year of Passing: " << yearOfPass << std::endl;
    std::cout << "Scholar ID: " << scholarID << std::endl;
}

