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

public:
    // Default constructor
    Student() : People(), branch(""), section(' '), yearOfPass(-1), scholarID(-1) {}

    // Parameterized constructor
    Student(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer, const std::string& _branch, char _section, const int& _yearOfPass, const int& _scholarID);
    
    // Getters
    std::string getBranch() const { return branch; }
    char getSection() const { return section; }
    int getYearOfPass() const { return yearOfPass; }
    int getScholarID() const { return scholarID; }

    // Setters
    void setBranch(const std::string& _branch) { branch = _branch; }
    void setSection(char _section) { section = _section; }
    void setYearOfPass(int _yearOfPass) { yearOfPass = _yearOfPass; }
    void setScholarID(int _scholarID) { scholarID = _scholarID; }
    
    bool login();
    bool signup();
    bool forgotPassword();
    void viewSubjects(bool onlySubjectCodes=false,bool onlyAttendance=false, const std::string&subjectCode="");
    void addSubject();
    void editSubject();
    void deleteSubject();
    void addAttendance();
    void editAttendance();
    void viewAttendance();
    void viewProfile();
    void editProfile();
};
#endif
