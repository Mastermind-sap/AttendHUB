#include "Student.h"
#include "customInput.h"
#include "DatabaseManager.h"
#include "Subject.h"

Student::Student(const std::string& _firstName, const std::string& _lastName, const std::string& _dob, const std::string& _username, const std::string& _password, const std::string& _secretAnswer, const std::string& _branch, char _section, const int& _yearOfPass, const int& _scholarID)
    : People(_firstName, _lastName, _dob, _username, _password, _secretAnswer), branch(_branch), section(_section), yearOfPass(_yearOfPass), scholarID(_scholarID) {}

bool Student::signup() {
    // Call the People::signup method to get common user details
    bool success = People::signup();
    if (success) {
        // Prompt for additional student details
        std::cout << "Enter scholar ID: ";
        takeInput(&scholarID);

        // Use DatabaseManager to add student to the database
        DatabaseManager dbManager;

        // Verifying if Scholar id is unique
        if (dbManager.isScholarIDExists(scholarID)) {
            std::cout << "Scholar ID already exists! Please enter valid scholar ID." << std::endl;
            return false;
        }

        std::cout << "Enter branch: ";
        takeInput(&branch);

        std::cout << "Enter section: ";
        takeInput(&section);

        std::cout << "Enter year of passing: ";
        takeInput(&yearOfPass);

        bool check=dbManager.addStudent(scholarID,firstName, lastName, dob, branch, section, yearOfPass, username, password, secretAnswer);
        if(check)
        {
            std::cout << "Student account created successfully!" << std::endl;
            std::cout << "Signup Successfull!!\n";
        }
        return check;
    }
    else {
        std::cout << "Signup Unsuccessfull!!\n";
        return false;
    }
}


bool Student::login() {
    if (People::login()) {
        DatabaseManager dbManager;
        dbManager.fetchDetails(*this, username);
        return true;
    }
    return false;
}

bool Student::forgotPassword() {
    if (People::forgotPassword()) {
        DatabaseManager dbManager;
        dbManager.fetchDetails(*this, username);
        return true;
    }
    return false;
}

void Student::viewProfile() {
    // Display common user details using People::showDetails method
    size_t columnWidth = showDetails();

    // Display student-specific details
    std::cout << "\t\t\t\t\t|     Branch         |" << branch << std::string(columnWidth - branch.length(), ' ') << "|" << std::endl;
    std::cout << "\t\t\t\t\t|     Section        |" << section << std::string(columnWidth - 1, ' ') << "|" << std::endl;
    std::cout << "\t\t\t\t\t|   Year of Passing  |" << yearOfPass << std::string(columnWidth - std::to_string(yearOfPass).length(), ' ') << "|" << std::endl;
    std::cout << "\t\t\t\t\t|     Scholar ID     |" << scholarID << std::string(columnWidth - std::to_string(scholarID).length(), ' ') << "|" << std::endl;
    std::cout << "\t\t\t\t\t+--------------------+" << std::string(columnWidth, '-') << "+ " << std::endl;
}






void Student::viewSubjects(bool onlySubjectCodes,bool onlyAttendance,const std::string&subjectCode)
{
    // Use DatabaseManager to view subjects for this student
    DatabaseManager dbManager;
    std::vector<SubjectDetails> subjects = dbManager.getSubjects(scholarID,subjectCode);

    // Print all subject details
    for (const auto& subject : subjects) {
        std::cout << "Subject Code: " << subject.subjectCode << std::endl;
        if(!onlySubjectCodes)
        {
            if(!onlyAttendance)
            {
                std::cout << "Subject Name: " << subject.subjectName << std::endl;
                std::cout << "Instructor Name: " << subject.instructorName << std::endl;
            }
            std::cout << "Total Classes: " << subject.totalClasses << std::endl;
            std::cout << "Classes Present: " << subject.classesPresent << std::endl;
            std::cout << "Classes Absent: " << subject.totalClasses-subject.classesPresent << std::endl;
            std::cout << "Attendance Percentage: " << ((float)subject.classesPresent/ (float)subject.totalClasses)*100.0<<" %" << std::endl;
        }
        std::cout << std::endl;
    }
}

void Student::addSubject()
{
    // Input subject details
    Subject subject;
    subject.inputDetails();

    if (subject.getTotalClasses() < 0 || subject.getClassesPresent() < 0 || subject.getClassesPresent() > subject.getTotalClasses()) {
        std::cout << "Invalid input. Please enter non-negative values, with classes present not exceeding total classes." << std::endl;
        return;
    }
    // Use DatabaseManager to add subject for this student
    DatabaseManager dbManager;
    dbManager.addSubject(scholarID, subject);
}

void Student::deleteSubject()
{
    viewSubjects(true);
    
    // Use DatabaseManager to fetch subjects for this student
    DatabaseManager dbManager;

    // Take user input for subject code to delete
    std::string subjectCode;
    std::cout << "Enter subject code to delete: ";
    takeInput(&subjectCode);


    // Check if the subject exists for this student
    if (!dbManager.subjectExists(scholarID, subjectCode))
    {
        std::cout << "Subject not found." << std::endl;
        return;
    }

    // Use DatabaseManager to delete subject for this student
    dbManager.deleteSubject(scholarID, subjectCode);
}

void Student::addAttendance()
{
    viewSubjects(true);
    
    // Use DatabaseManager to fetch subjects for this student
    DatabaseManager dbManager;

    // Take user input for subject code to add attendance
    std::string subjectCode;
    std::cout << "Enter subject code to add attendance: ";
    takeInput(&subjectCode);

    // Check if the subject exists for this student
    if (!dbManager.subjectExists(scholarID, subjectCode))
    {
        std::cout << "Subject not found." << std::endl;
        return;
    }

    auto subjects = dbManager.getSubjects(scholarID, subjectCode);
    // Take user input for attendance status (present or absent)
    char attendanceStatus;
    std::cout << "Enter attendance status (P for present, A for absent): ";
    takeInput(&attendanceStatus);

    if (attendanceStatus == 'P' || attendanceStatus == 'p')
    {
        subjects[0].totalClasses += 1;
        subjects[0].classesPresent += 1;
    }
    else if (attendanceStatus == 'A' || attendanceStatus == 'a')
    {
        subjects[0].totalClasses += 1;
    }
    else
    {
        std::cout << "Invalid input. Please enter 'P' for present or 'A' for absent." << std::endl;
        return;
    }

    // Use DatabaseManager to add attendance for this student
    dbManager.updateSubject(scholarID,subjectCode,subjects[0].subjectName,subjects[0].instructorName,subjects[0].totalClasses,subjects[0].classesPresent);
}

void Student::editAttendance()
{
    viewSubjects(true);

    // Use DatabaseManager to fetch subjects for this student
    DatabaseManager dbManager;

    // Take user input for subject code to edit attendance
    std::string subjectCode;
    std::cout << "Enter subject code to edit attendance: ";
    takeInput(&subjectCode);

    // Check if the subject exists for this student
    if (!dbManager.subjectExists(scholarID, subjectCode))
    {
        std::cout << "Subject not found." << std::endl;
        return;
    }

    auto subjects = dbManager.getSubjects(scholarID, subjectCode);

    // Take user input for new attendance details
    int newClassesPresent, newTotalClasses;
    std::cout << "Enter new total classes: ";
    takeInput(&newTotalClasses);
    std::cout << "Enter new classes present: ";
    takeInput(&newClassesPresent);

    // Validate input
    if (newTotalClasses < 0 || newClassesPresent < 0 || newClassesPresent > newTotalClasses)
    {
        std::cout << "Invalid input. Please enter non-negative values, with classes present not exceeding total classes." << std::endl;
        return;
    }

    // Use DatabaseManager to edit attendance for this student
    dbManager.updateSubject(scholarID, subjectCode, subjects[0].subjectName, subjects[0].instructorName, newTotalClasses, newClassesPresent);
}

void Student::viewAttendance()
{
    viewSubjects(true);

    // Use DatabaseManager to fetch subjects for this student
    DatabaseManager dbManager;

    // Take user input for subject code to view attendance
    std::string subjectCode;
    std::cout << "Enter subject code to view attendance(or press enter to view all): ";
    takeInput(&subjectCode);

    // Check if the subject exists for this student
    if (!dbManager.subjectExists(scholarID, subjectCode)&&subjectCode!="")
    {
        std::cout << "Subject not found." << std::endl;
        return;
    }
    viewSubjects(false, true, subjectCode);
}