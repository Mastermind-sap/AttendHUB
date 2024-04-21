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
        std::cout << "\t\t\t\tEnter scholar ID: ";
        takeInput(&scholarID);

        // Use DatabaseManager to add student to the database
        DatabaseManager dbManager;

        // Verifying if Scholar id is unique
        if (dbManager.isScholarIDExists(scholarID)) {
            std::cout << "\t\t\t\tScholar ID already exists! Please enter valid scholar ID." << std::endl;
            return false;
        }

        std::cout << "\t\t\t\tEnter branch: ";
        takeInput(&branch);

        std::cout << "\t\t\t\tEnter section: ";
        takeInput(&section);

        std::cout << "\t\t\t\tEnter year of passing: ";
        takeInput(&yearOfPass);

        bool check=dbManager.addStudent(scholarID,firstName, lastName, dob, branch, section, yearOfPass, username, password, secretAnswer);
        if(check)
        {
            std::cout << "\n\t\t\t\tStudent account created successfully!" << std::endl;
            std::cout << "\t\t\t\tSignup Successfull!!\n";
        }
        return check;
    }
    else {
        std::cout << "\n\t\t\t\tSignup Unsuccessfull!!\n";
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

void Student::editProfile() {
    // Use DatabaseManager to fetch student details
    DatabaseManager dbManager;

    std::cout << "Enter new details(Press enter on fields you dont want to change):" << std::endl;

    // Take new details from the user
    int _yearOfPass;
    std::string _firstName, _lastName, _dob, _branch, _username, _secret;
    char _section;
    std::cout << "Enter new username: ";
    if (takeInput(&_username, false, true)) {
        if (dbManager.isUsernameExists(_username)&&_username!=username) {
            std::cout << "\n\t\t\t\tUsername already exists! Please choose another username.\n" << std::endl;
            return;
        }
        setUsername(_username);
    }
    std::cout << "Enter new first name: ";
    if (takeInput(&_firstName, false, true)) {
       setFirstName(_firstName);
    }

    std::cout << "Enter new last name: ";
    if (takeInput(&_lastName, false, true)) {
       setLastName(_lastName);
    }

    std::cout << "Enter new Date of Birth: ";
    if (takeInput(&_dob, false, true)) {
        setDOB(_dob);
    }

    std::cout << "Enter new branch: ";
    if (takeInput(&_branch, false, true)) {
        setBranch(_branch);
    }

    std::cout << "Enter new section: ";
    if (takeInput(&_section, false, true)) {
        setSection(_section);
    }

    std::cout << "Enter new year of pass: ";
    if (takeInput(&_yearOfPass, false, true)) {
        setYearOfPass(_yearOfPass);
    }

    std::cout << "Enter new secret answer: ";
    if (takeInput(&_secret, false, true)) {
        setSecretAnswer(_secret);
    }

    // Update student details in the database
    dbManager.updateStudent(*this);
    // Just to be sure that there is no data discrepancy fetch the details after they are updated
    dbManager.fetchDetails(*this, username);
    std::cout << "Profile updated successfully!" << std::endl;
}





void Student::viewSubjects(bool onlySubjectCodes,bool onlyAttendance,const std::string&subjectCode)
{
    // Use DatabaseManager to view subjects for this student
    DatabaseManager dbManager;
    std::vector<Subject> subjects = dbManager.getSubjects(scholarID,subjectCode);

    // Print all subject details
    for (const auto& subject : subjects) {
        std::cout << "Subject Code: " << subject.getSubjectCode() << std::endl;
        if(!onlySubjectCodes)
        {
            if(!onlyAttendance)
            {
                std::cout << "Subject Name: " << subject.getSubjectName()<< std::endl;
                std::cout << "Instructor Name: " << subject.getInstructorName() << std::endl;
            }
            std::cout << "Total Classes: " << subject.getTotalClasses() << std::endl;
            std::cout << "Classes Present: " << subject.getClassesPresent()<< std::endl;
            std::cout << "Classes Absent: " << subject.getTotalClasses() - subject.getClassesPresent() << std::endl;
            std::cout << "Attendance Percentage: " << ((float)subject.getClassesPresent() / (float)subject.getTotalClasses())*100.0<<" %" << std::endl;
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

void Student::editSubject()
{
    viewSubjects(true);

    // Use DatabaseManager to fetch subjects for this student
    DatabaseManager dbManager;

    // Take user input for subject code to edit
    std::string _subjectCode;
    std::cout << "Enter subject code to edit: ";
    takeInput(&_subjectCode);


    // Check if the subject exists for this student
    auto subjects = dbManager.getSubjects(scholarID, _subjectCode);
    if (subjects.size()==0)
    {
        std::cout << "Subject not found." << std::endl;
        return;
    }

    Subject subject = subjects[0];
    subject.inputDetails(false,false);

    if (subject.getTotalClasses() < 0 || subject.getClassesPresent() < 0 || subject.getClassesPresent() > subject.getTotalClasses()) {
        std::cout << "Invalid input. Please enter non-negative values, with classes present not exceeding total classes." << std::endl;
        return;
    }
    // Use DatabaseManager to edit subject for this student
    dbManager.updateSubject(scholarID, subject);
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
        subjects[0].setTotalClasses(subjects[0].getTotalClasses()+ 1);
        subjects[0].setClassesPresent(subjects[0].getClassesPresent() + 1);
    }
    else if (attendanceStatus == 'A' || attendanceStatus == 'a')
    {
        subjects[0].setTotalClasses(subjects[0].getTotalClasses() + 1);
    }
    else
    {
        std::cout << "Invalid input. Please enter 'P' for present or 'A' for absent." << std::endl;
        return;
    }

    // Use DatabaseManager to add attendance for this student
    dbManager.updateSubject(scholarID,subjects[0]);
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
    subjects[0].setTotalClasses(newTotalClasses);
    subjects[0].setClassesPresent(newClassesPresent);
    // Use DatabaseManager to edit attendance for this student
    dbManager.updateSubject(scholarID, subjects[0]);
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