#include "Admin.h"

Admin::Admin(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer, const std::string& _adminCode)
    : People(_firstName, _lastName, _dob, _username, _password, _secretAnswer), adminCode(_adminCode) {}

void Admin::assignInstructor(const std::string& instructorCode, const std::string& _class) {
    // Implement assigning instructor to class
}

void Admin::addClass(const std::string& instructorCode, const std::string& branch, char section, const std::string& subject, int noOfStudents, const std::vector<std::string>& scholarIds) {
    // Implement adding class
}