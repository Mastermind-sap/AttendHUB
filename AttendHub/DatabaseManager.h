//#pragma once
#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <sqlite3.h>
#include <string>
#include "Student.h"
#include "Subject.h"

class DatabaseManager {
private:
    sqlite3* db;
    std::string dbName;

public:
    // Constructor
    // Change the dbName according to where you want to store the sqlite database
    DatabaseManager(const std::string& dbName="..\\data.db");

    // Destructor
    ~DatabaseManager();

    void createTablesIfNotExist();




    // Function to create a table for a specific scholar ID and subject code
    void createSubjectTable(const std::string& scholarID, const std::string& subjectCode);



    // CRUD functions for student table
    bool isUsernameExists(const std::string& username, const std::string& type = "students");
    bool verifyUser(const std::string& username, const std::string& password, const std::string& type = "students");
    bool verifySecret(std::string username, std::string secret, const std::string& type="students");
    bool changePassword(const std::string& username, const std::string& newPassword, const std::string& type="students");
    void fetchDetails(Student& student, const std::string& username);
    bool addStudent(const std::string& firstName, const std::string& lastName, const std::string& dob, const std::string& branch, char section, int yearOfPass, const std::string& username, const std::string& password, const std::string& secret);
    void deleteStudent(int scholarID);
    void updateStudent(int scholarID, const std::string& firstName, const std::string& lastName, const std::string& dob, const std::string& branch, char section, int yearOfPass, const std::string& username, const std::string& password, const std::string& secret);
    void viewStudent(int scholarID);

    // CRUD functions for classes table
    bool subjectExists(int scholarID, const std::string& subjectCode);
    std::vector<SubjectDetails> getSubjects(int scholarID, const std::string& subjectCode="");
    void addSubject(int scholarID, const Subject& subject);
    void deleteSubject(int scholarID, const std::string& subjectCode);
    void updateSubject(int scholarID, const std::string& subjectCode, const std::string& subjectName, const std::string& instructorName, int totalClasses, int classesPresent);
    void viewSubjects(int scholarID);
};
#endif
