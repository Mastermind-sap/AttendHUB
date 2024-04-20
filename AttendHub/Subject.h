//#pragma once
#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include "customInput.h"

class Subject {
private:
    std::string subjectCode;
    std::string subjectName;
    std::string instructorName;
    int totalClasses;
    int classesPresent;

public:
    // Constructors
    Subject();
    Subject(const std::string& _subjectCode);
    Subject(const std::string& _subjectCode, const std::string& _subjectName, const std::string& _instructorName, int _totalClasses, int _classesPresent);

    // Function to input details
    void inputDetails(bool takeCode=true);

    // Function to display details
    void displayDetails() const;

    // Getters
    std::string getSubjectCode() const { return subjectCode; }
    std::string getSubjectName() const { return subjectName; }
    std::string getInstructorName() const { return instructorName; }
    int getTotalClasses() const { return totalClasses; }
    int getClassesPresent() const { return classesPresent; }

    // Setters
    void setSubjectCode(const std::string& _subjectCode) { subjectCode = _subjectCode; }
    void setSubjectName(const std::string& _subjectName) { subjectName = _subjectName; }
    void setInstructorName(const std::string& _instructorName) { instructorName = _instructorName; }
    void setTotalClasses(int _totalClasses) { totalClasses = _totalClasses; }
    void setClassesPresent(int _classesPresent) { classesPresent = _classesPresent; }

};

#endif
