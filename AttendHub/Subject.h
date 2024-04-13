#pragma once
#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>

class Subject {
private:
    std::string subjectCode;
    std::string subjectName;
    std::string instructorName;
    int totalClasses;
    int classesPresent;

public:
    // Constructor
    Subject(const std::string& subjectCode);

    // Function to input extra details
    void inputDetails();

    // Function to display subject details
    void displayDetails() const;
};

#endif
