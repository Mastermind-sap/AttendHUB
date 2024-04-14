//#pragma once
#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include "customInput.h"

// Define a struct to hold subject details
    struct SubjectDetails {
        std::string subjectCode;
        std::string subjectName;
        std::string instructorName;
        int totalClasses;
        int classesPresent;
    };

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
    Subject(const std::string& _subjectCode, const std::string& _subjectName, const std::string& _instructorName, int _totalClasses, int _classesPresent);

    // Function to input details
    void inputDetails();

    // Function to display details
    void displayDetails() const;

    // Getters
    std::string getSubjectCode() const { return subjectCode; }
    std::string getSubjectName() const { return subjectName; }
    std::string getInstructorName() const { return instructorName; }
    int getTotalClasses() const { return totalClasses; }
    int getClassesPresent() const { return classesPresent; }
};

#endif
