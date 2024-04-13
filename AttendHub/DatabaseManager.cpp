#include "DatabaseManager.h"
#include <iostream>
#include <sstream>

// Constructor
DatabaseManager::DatabaseManager(const std::string& _dbName) : dbName(_dbName) {
    int exit = sqlite3_open(dbName.c_str(), &db);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }
    else {
        // Create tables if they don't exist
        createTablesIfNotExist();
    }
}

// Destructor
DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
}

// Function to create tables if they don't exist
void DatabaseManager::createTablesIfNotExist() {
    // SQL command to create students table
    std::string createStudentsTableSQL = "CREATE TABLE IF NOT EXISTS students ("
        "scholar_id INTEGER PRIMARY KEY, "
        "first_name TEXT, "
        "last_name TEXT, "
        "dob TEXT, "
        "branch TEXT, "
        "section CHAR, "
        "year_of_pass INT, "
        "username TEXT, "
        "password TEXT, "
        "secret TEXT "
        ");";

    // SQL command to create classes table
    std::string createClassesTableSQL = "CREATE TABLE IF NOT EXISTS classes ("
        "scholar_id INTEGER PRIMARY KEY, "
        "subject_code TEXT, "
        "subject_name TEXT, "
        "instructor_name TEXT, "
        "total_classes INT, "
        "classes_present INT, "
        "FOREIGN KEY(scholar_id) REFERENCES students(scholar_id)"
        ");";

    // Execute SQL commands
    char* messageError;
    int exit = sqlite3_exec(db, createStudentsTableSQL.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error creating students table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }

    exit = sqlite3_exec(db, createClassesTableSQL.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error creating classes table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
}

// Function to check if username already exists
bool DatabaseManager::isUsernameExists(const std::string& username, const std::string& type) {
    std::string sql = "SELECT COUNT(*) FROM "+type+" WHERE username = '" + username + "'; ";
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return (count > 0);
        }
    }
    sqlite3_finalize(stmt);
    return false;
}

// Function to verify User
bool DatabaseManager::verifyUser(const std::string& username, const std::string& password, const std::string& type) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT COUNT(*) FROM " + type + " WHERE username = '"+username+"' AND password = '"+ password +"' ; ";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    //std::cout << result << std::endl;
    if (result == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
        //std::cout << "SQL Query: " << sql << std::endl;
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            //std::cout << count << std::endl;
            return (count > 0);
        }
    }
    else {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    //std::cout<<"FAILED\n";
    return false;
}

void DatabaseManager::fetchDetails(Student& student, const std::string& username) {
    // Fetch student details from the database using the provided username
    std::string sql = "SELECT * FROM students WHERE username = '" + username + "';";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        // Execute the query
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            // Retrieve values from the database
            int scholarID = sqlite3_column_int(stmt, 0);
            std::string firstName = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string lastName = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            std::string dob = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            std::string branch = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            char section = static_cast<char>(sqlite3_column_text(stmt, 5)[0]);
            int yearOfPass = sqlite3_column_int(stmt, 6);
            std::string user = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
            std::string pass = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
            std::string secret = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));

            // Set the values of the student object
            student.setScholarID(scholarID);
            student.setFirstName(firstName);
            student.setLastName(lastName);
            student.setDOB(dob);
            student.setBranch(branch);
            student.setSection(section);
            student.setYearOfPass(yearOfPass);
            student.setUsername(user);
            student.setPassword(pass);
            student.setSecretAnswer(secret);
        }
    }
    sqlite3_finalize(stmt);
}


// Function to add a student to the students table
bool DatabaseManager::addStudent(const std::string& firstName, const std::string& lastName, const std::string& dob, const std::string& branch, char section, int yearOfPass, const std::string& username, const std::string& password, const std::string& secret) {
    std::string sql = "INSERT INTO students (first_name, last_name, dob, branch, section, year_of_pass, username, password, secret) VALUES ('" + firstName + "', '" + lastName + "', '" + dob + "', '" + branch + "', '" + std::string(1, section) + "', " + std::to_string(yearOfPass) + ", '" + username + "', '" + password + "', '" + secret + "');";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error adding student: " << messageError << std::endl;
        sqlite3_free(messageError);
        return false;
    }
    else {
        return true;
    }
}

// Function to delete a student from the students table
void DatabaseManager::deleteStudent(int scholarID) {
    std::string sql = "DELETE FROM students WHERE scholar_id = " + std::to_string(scholarID) + ";";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error deleting student: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else {
        std::cout << "Student deleted successfully!" << std::endl;
    }
}

// Function to update student details in the students table
void DatabaseManager::updateStudent(int scholarID, const std::string& firstName, const std::string& lastName, const std::string& dob, const std::string& branch, char section, int yearOfPass, const std::string& username, const std::string& password, const std::string& secret) {
    std::string sql = "UPDATE students SET first_name = '" + firstName + "', last_name = '" + lastName + "', dob = '" + dob + "', branch = '" + branch + "', section = '" + std::string(1, section) + "', year_of_pass = " + std::to_string(yearOfPass) + ", username = '" + username + "', password = '" + password + "', secret = '" + secret + "' WHERE scholar_id = " + std::to_string(scholarID) + ";";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error updating student: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else {
        std::cout << "Student updated successfully!" << std::endl;
    }
}

// Function to view student details from the students table
void DatabaseManager::viewStudent(int scholarID) {
    std::string sql = "SELECT * FROM students WHERE scholar_id = " + std::to_string(scholarID) + ";";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error viewing student: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
}

// Function to add a subject to the classes table
void DatabaseManager::addSubject(int scholarID, const std::string& subjectCode, const std::string& subjectName, const std::string& instructorName, int totalClasses, int classesPresent) {
    std::string sql = "INSERT INTO classes (scholar_id, subject_code, subject_name, instructor_name, total_classes, classes_present) VALUES (" + std::to_string(scholarID) + ", '" + subjectCode + "', '" + subjectName + "', '" + instructorName + "', " + std::to_string(totalClasses) + ", " + std::to_string(classesPresent) + ");";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error adding subject: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else {
        std::cout << "Subject added successfully!" << std::endl;
    }
}

// Function to delete a subject from the classes table
void DatabaseManager::deleteSubject(int scholarID, const std::string& subjectCode) {
    std::string sql = "DELETE FROM classes WHERE scholar_id = " + std::to_string(scholarID) + " AND subject_code = '" + subjectCode + "';";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error deleting subject: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else {
        std::cout << "Subject deleted successfully!" << std::endl;
    }
}

// Function to update subject details in the classes table
void DatabaseManager::updateSubject(int scholarID, const std::string& subjectCode, const std::string& subjectName, const std::string& instructorName, int totalClasses, int classesPresent) {
    std::string sql = "UPDATE classes SET subject_name = '" + subjectName + "', instructor_name = '" + instructorName + "', total_classes = " + std::to_string(totalClasses) + ", classes_present = " + std::to_string(classesPresent) + " WHERE scholar_id = " + std::to_string(scholarID) + " AND subject_code = '" + subjectCode + "';";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error updating subject: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else {
        std::cout << "Subject updated successfully!" << std::endl;
    }
}

// Function to view subjects for a specific student from the classes table
void DatabaseManager::viewSubjects(int scholarID) {
    std::string sql = "SELECT * FROM classes WHERE scholar_id = " + std::to_string(scholarID) + ";";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error viewing subjects: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
}


// Function to create a table for a specific scholar ID and subject code
void DatabaseManager::createSubjectTable(const std::string& scholarID, const std::string& subjectCode) {
    std::stringstream tableName;
    tableName << "table_" << scholarID << "_" << subjectCode;

    std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName.str() + " (date TEXT PRIMARY KEY, present BOOLEAN);";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error creating subject table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else {
        std::cout << "Subject table created successfully!" << std::endl;
    }
}