//#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include "People.h"
#include <vector>

class Student : public People {
private:
    std::string branch;
    char section;
    int yearOfPass;
    int scholarID;
    std::vector<std::string> subjects;

public:
    // Default constructor
    Student() : People(), branch(""), section(' '), yearOfPass(-1), scholarID(-1), subjects({}) {}

    // Parameterized constructor
    Student(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer, const std::string& _branch, char _section, const std::string& _yearOfPass, const std::string& _scholarID);
    void viewAttendance();
};
#endif
