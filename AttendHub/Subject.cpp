#include "Subject.h"
#include "customInput.h"
#include <iostream>

// Default Constructor
Subject::Subject() : subjectCode(""),subjectName(""),instructorName(""), totalClasses(0), classesPresent(0) {}

// Constructor
Subject::Subject(const std::string& _subjectCode, const std::string& _subjectName, const std::string& _instructorName, int _totalClasses, int _classesPresent)
    : subjectCode(_subjectCode), subjectName(_subjectName), instructorName(_instructorName), totalClasses(_totalClasses), classesPresent(_classesPresent) {}
Subject::Subject(const std::string& _subjectCode):subjectCode(_subjectCode), subjectName(""), instructorName(""), totalClasses(0), classesPresent(0) {}

// Function to input details
void Subject::inputDetails(bool takeCode,bool initialInput) {
    if (!initialInput) {
        std::cout << "Enter new details(Press enter on fields you dont want to change):" << std::endl;
    }
    if(takeCode)
    {
        std::cout << "Enter subject code: ";
        takeInput(&subjectCode);
    }

    std::string _subjectName, _instructorName;
    int _totalClasses, _classesPresent;
    std::cout << "Enter subject name: ";
    //checks whether it is empty or not
    if (takeInput(&_subjectName, true, !initialInput))
        setSubjectName(_subjectName);

    std::cout << "Enter instructor name: ";
    if (takeInput(&_instructorName, true, !initialInput))
        setInstructorName(_instructorName);

    std::cout << "Enter total classes: ";
    if (takeInput(&_totalClasses, true, !initialInput)) {
        setTotalClasses(_totalClasses);
    }

    std::cout << "Enter classes present: ";
    if (takeInput(&_classesPresent, true, !initialInput)) { 
        setClassesPresent(_classesPresent); 
    }
}

// Function to display details
void Subject::displayDetails() const {
    std::cout << "Subject Code: " << subjectCode << std::endl;
    std::cout << "Subject Name: " << subjectName << std::endl;
    std::cout << "Instructor Name: " << instructorName << std::endl;
    std::cout << "Total Classes: " << totalClasses << std::endl;
    std::cout << "Classes Present: " << classesPresent << std::endl;
}
