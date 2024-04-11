//#pragma once
#ifndef CLASS_H
#define CLASS_H

#include <string>

class Class {
private:
    std::string branch;
    std::string subject;
    std::string section;
    std::string instructorCode;

public:
    Class(const std::string& _branch, const std::string& _subject, const std::string& _section, const std::string& _instructorCode);
};

#endif // CLASS_H


