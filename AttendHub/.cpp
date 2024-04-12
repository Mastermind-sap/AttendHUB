#include "Instructor.h"

Instructor::Instructor(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer, const std::string& _instructorCode, const std::string& _department)
    : People(_firstName, _lastName, _dob, _username, _password, _secretAnswer), instructorCode(_instructorCode), department(_department) {}

void Instructor::editAttendance(const std::string& _class) {
    // Implement edit attendance for class
}

void Instructor::viewAttendance(const std::string& _class) {
    // Implement view attendance for class
}
