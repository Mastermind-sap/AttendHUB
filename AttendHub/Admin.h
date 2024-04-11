// Pragma is compiler specific and can cause error so use
// Pragma is faster although it can cause error as it doesnot goes throught the entire file
// Refer: https://64.github.io/cpp-faq/include-guards-pragma-once/#:~:text=Include%20guards%2C%20or%20sometimes%20called,equivalent%20alternative%20to%20this%20idiom.
//#pragma once
//if pragma once causes error:
#ifndef ADMIN_H
#define ADMIN_H
#include "People.h"
#include<vector>
class Admin : public People {
private:
    std::string adminCode;

public:
    Admin(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer, const std::string& _adminCode);
    void assignInstructor(const std::string& instructorCode, const std::string& _class);
    void addClass(const std::string& instructorCode, const std::string& branch, char section, const std::string& subject, int noOfStudents, const std::vector<std::string>& scholarIds);
};
#endif