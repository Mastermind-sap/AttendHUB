#include "Student.h"

Student::Student(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer, const std::string& _branch, char _section, const std::string& _yearOfPass, const std::string& _scholarID)
    : People(_firstName, _lastName, _dob, _username, _password, _secretAnswer), branch(_branch), section(_section), yearOfPass(_yearOfPass), scholarID(_scholarID) {}

void Student::viewAttendance() {
    // Implement view attendance for student
}