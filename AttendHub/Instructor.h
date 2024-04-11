//#pragma once
#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include "People.h"
#include <vector>

class Instructor : public People {
private:
    std::string instructorCode;
    std::string department;
    std::vector<std::string> classes;

public:
    Instructor(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer, const std::string& _instructorCode, const std::string& _department);
    void editAttendance(const std::string& _class);
    void viewAttendance(const std::string& _class);
};
#endif

