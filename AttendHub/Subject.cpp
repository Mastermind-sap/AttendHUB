#include "Subject.h"
#include "customInput.h"

// Constructor definition
Subject::Subject(const std::string& _subjectCode) : subjectCode(_subjectCode) {}

// Function to input extra details
void Subject::inputDetails() {
    std::cout << "Enter subject name: ";
    takeInput(&subjectName);

    std::cout << "Enter instructor name: ";
    takeInput(&instructorName);

    std::cout << "Enter total classes: ";
    takeInput(&totalClasses);

    std::cout << "Enter classes present: ";
    takeInput(&classesPresent);
}

// Function to display subject details
void Subject::displayDetails() const {
    std::cout << "Subject Code: " << subjectCode << std::endl;
    std::cout << "Subject Name: " << subjectName << std::endl;
    std::cout << "Instructor Name: " << instructorName << std::endl;
    std::cout << "Total Classes: " << totalClasses << std::endl;
    std::cout << "Classes Present: " << classesPresent << std::endl;
}
