#include "DatabaseManager.h"
#include <iostream>
#include <sstream>

// Constructor
DatabaseManager::DatabaseManager(const std::string& _dbName) : dbName(_dbName) {
    int exit = sqlite3_open(dbName.c_str(), &db);
    if (exit != SQLITE_OK) {
        std::cerr << "\t\t\tError opening database: " << sqlite3_errmsg(db) << std::endl;
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
        "first_name TEXT NOT NULL, "
        "last_name TEXT NOT NULL, "
        "dob TEXT NOT NULL, "
        "branch TEXT NOT NULL, "
        "section CHAR NOT NULL, "
        "year_of_pass INT NOT NULL, "
        "username TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL, "
        "secret TEXT NOT NULL"
        ");";

    // SQL command to create classes table with composite primary key
    std::string createClassesTableSQL = "CREATE TABLE IF NOT EXISTS classes ("
        "scholar_id INTEGER NOT NULL, "
        "subject_code TEXT NOT NULL, "
        "subject_name TEXT NOT NULL, "
        "instructor_name TEXT NOT NULL, "
        "total_classes INT NOT NULL, "
        "classes_present INT NOT NULL, "
        "PRIMARY KEY (scholar_id, subject_code), "
        "FOREIGN KEY(scholar_id) REFERENCES students(scholar_id)"
        ");";


    // Execute SQL commands
    char* messageError;
    int exit = sqlite3_exec(db, createStudentsTableSQL.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "\t\t\tError creating students table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }

    exit = sqlite3_exec(db, createClassesTableSQL.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "\t\t\tError creating classes table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
}

// Function to check if username already exists
bool DatabaseManager::isUsernameExists(const std::string& username, const std::string& type) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT COUNT(*) FROM " + type + " WHERE username = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return (count > 0);
        }
    }
    sqlite3_finalize(stmt);
    return false;
}

// Function to check if scholar Id already exists
bool DatabaseManager::isScholarIDExists(int scholarID , const std::string& type) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT COUNT(*) FROM " + type + " WHERE scholar_id = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, scholarID);
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
    std::string sql = "SELECT COUNT(*) FROM " + type + " WHERE username = ? AND password = ?;";
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return (count > 0);
        }
    }
    sqlite3_finalize(stmt);
    return false;
}

bool DatabaseManager::verifySecret(std::string username, std::string secret, const std::string& type) {
    // Check if the username and secret match in the database
    std::string sql = "SELECT COUNT(*) FROM "+type+" WHERE username = ? AND secret = ?;";
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, secret.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            if(count>0)
            {
                std::cout << "\t\t\tWelcome back " + username << std::endl;
            }
            else {
                std::cout << "\t\t\tEither the username or the secret entered was wrong!" << std::endl;
            }
            return (count > 0);
        }
    }
    std::cout << "\t\t\tVerification unsuccessful!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
}

bool DatabaseManager::changePassword(const std::string& username, const std::string& newPassword, const std::string& type) {
    // Update the password in the database
    std::string sql = "UPDATE "+type+" SET password = ? WHERE username = ?;";
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            std::cout << "\t\t\tPassword changed successfully!" << std::endl;
            return true;
        }
        else {
            std::cerr << "\t\t\tError changing password: " << sqlite3_errmsg(db) << std::endl;
        }
    }
    else {
        std::cerr << "\t\t\tError preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    return false;
    sqlite3_finalize(stmt);
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
bool DatabaseManager::addStudent(int scholarId,const std::string& firstName, const std::string& lastName, const std::string& dob, const std::string& branch, char section, int yearOfPass, const std::string& username, const std::string& password, const std::string& secret) {
    std::string sql = "INSERT INTO students (scholar_id,first_name, last_name, dob, branch, section, year_of_pass, username, password, secret) VALUES ( "+ std::to_string(scholarId)+", '" + firstName + "', '" + lastName + "', '" + dob + "', '" + branch + "', '" + std::string(1, section) + "', " + std::to_string(yearOfPass) + ", '" + username + "', '" + password + "', '" + secret + "'); ";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "\t\t\tError adding student: " << messageError << std::endl;
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
        std::cerr << "\t\t\tError deleting student: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else {
        std::cout << "\t\t\tStudent deleted successfully!" << std::endl;
    }
}

// Function to update student details in the students table
void DatabaseManager::updateStudent(const Student& student) {
    std::string sql = "UPDATE students SET first_name = ?, last_name = ?, dob = ?, branch = ?, section = ?, year_of_pass = ?, username = ?, secret = ? WHERE scholar_id = ?;";

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        // Bind parameters
        sqlite3_bind_text(stmt, 1, student.getFirstName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, student.getLastName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, student.getDOB().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, student.getBranch().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, std::string(1, student.getSection()).c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 6, student.getYearOfPass());
        sqlite3_bind_text(stmt, 7, student.getUsername().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 8, student.getSecretAnswer().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 9, student.getScholarID());

        // Execute the query
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "\t\t\tError updating student: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "\t\t\tStudent updated successfully!" << std::endl;
        }

        // Finalize the statement
        sqlite3_finalize(stmt);
    }
    else {
        std::cerr << "\t\t\tError preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
}

// Function to view student details from the students table
void DatabaseManager::viewStudent(int scholarID) {
    std::string sql = "SELECT * FROM students WHERE scholar_id = " + std::to_string(scholarID) + ";";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "\t\t\tError viewing student: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
}






// Function to check if a subject exists for a specific student
bool DatabaseManager::subjectExists(int scholarID, const std::string& subjectCode) {
    std::string sql = "SELECT COUNT(*) FROM classes WHERE scholar_id = ? AND subject_code = ?;";

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, scholarID);
        sqlite3_bind_text(stmt, 2, subjectCode.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return (count > 0);
        }
    }
    else {
        std::cerr << "\t\t\tError preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return false;
}


// Function to add a subject to the classes table
void DatabaseManager::addSubject(int scholarID, const Subject& subject) {
    std::string sql = "INSERT INTO classes (scholar_id, subject_code, subject_name, instructor_name, total_classes, classes_present) VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, scholarID);
        sqlite3_bind_text(stmt, 2, subject.getSubjectCode().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, subject.getSubjectName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, subject.getInstructorName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 5, subject.getTotalClasses());
        sqlite3_bind_int(stmt, 6, subject.getClassesPresent());

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "\t\t\tError adding subject: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "\t\t\tSubject added successfully!" << std::endl;
        }
    }
    else {
        std::cerr << "\t\t\tError preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Function to update a subject in the classes table
void DatabaseManager::updateSubject(int scholarID, const Subject& subject) {
    std::string sql = "UPDATE classes SET subject_name = ?, instructor_name = ?, total_classes = ?, classes_present = ? WHERE scholar_id = ? AND subject_code = ?;";

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, subject.getSubjectName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, subject.getInstructorName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, subject.getTotalClasses());
        sqlite3_bind_int(stmt, 4, subject.getClassesPresent());
        sqlite3_bind_int(stmt, 5, scholarID);
        sqlite3_bind_text(stmt, 6, subject.getSubjectCode().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "\t\t\tError updating subject: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "\t\t\tSubject updated successfully!" << std::endl;
        }
    }
    else {
        std::cerr << "\t\t\tError preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Function to delete a subject from the classes table
void DatabaseManager::deleteSubject(int scholarID, const std::string& subjectCode) {
    std::string sql = "DELETE FROM classes WHERE scholar_id = ? AND subject_code = ?;";

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, scholarID);
        sqlite3_bind_text(stmt, 2, subjectCode.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "\t\t\tError deleting subject: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "\t\t\tSubject deleted successfully!" << std::endl;
        }
    }
    else {
        std::cerr << "\t\t\tError preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Function to view subjects for a specific student from the classes table
void DatabaseManager::viewSubjects(int scholarID) {
    // Prepare the SQL query with parameterized statement
    std::string sql = "SELECT * FROM classes WHERE scholar_id = ?;";

    // Prepare the SQL statement
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        // Bind scholarID as parameter
        sqlite3_bind_int(stmt, 1, scholarID);

        // Execute the query
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Retrieve values from the database and print them (similar to your previous implementation)
            int scholar_id = sqlite3_column_int(stmt, 0);
            const unsigned char* subject_code = sqlite3_column_text(stmt, 1);
            const unsigned char* subject_name = sqlite3_column_text(stmt, 2);
            const unsigned char* instructor_name = sqlite3_column_text(stmt, 3);
            int total_classes = sqlite3_column_int(stmt, 4);
            int classes_present = sqlite3_column_int(stmt, 5);

            // Output the retrieved data
            std::cout << "\t\t\tScholar ID: " << scholar_id << std::endl;
            std::cout << "\t\t\tSubject Code: " << subject_code << std::endl;
            std::cout << "\t\t\tSubject Name: " << subject_name << std::endl;
            std::cout << "\t\t\tInstructor Name: " << instructor_name << std::endl;
            std::cout << "\t\t\tTotal Classes: " << total_classes << std::endl;
            std::cout << "\t\t\tClasses Present: " << classes_present << std::endl;
            std::cout << std::endl;
        }

        // Finalize the statement
        sqlite3_finalize(stmt);
    }
    else {
        // Error handling if the SQL statement preparation fails
        std::cerr << "\t\t\tError preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
}

// Function to view subjects for a specific student from the classes table
std::vector<Subject> DatabaseManager::getSubjects(int scholarID, const std::string& subjectCode) {
    std::vector<Subject> subjects;

    // Prepare the SQL query with parameterized statement
    std::string sql;
    if (!subjectCode.empty()) {
        sql = "SELECT * FROM classes WHERE scholar_id = ? AND subject_code = ?;";
    }
    else {
        sql = "SELECT * FROM classes WHERE scholar_id = ?;";
    }

    // Prepare the SQL statement
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (result == SQLITE_OK) {
        // Bind scholarID as parameter
        sqlite3_bind_int(stmt, 1, scholarID);

        if (!subjectCode.empty()) {
            // Bind subjectCode as parameter if provided
            sqlite3_bind_text(stmt, 2, subjectCode.c_str(), -1, SQLITE_STATIC);
        }

        // Execute the query
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Retrieve values from the database and store them in the Subject object
            Subject subject(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                sqlite3_column_int(stmt, 4),
                sqlite3_column_int(stmt, 5));
            // Push the Subject object into the vector
            subjects.push_back(subject);
        }

        // Finalize the statement
        sqlite3_finalize(stmt);
    }
    else {
        // Error handling if the SQL statement preparation fails
        std::cerr << "\t\t\tError preparing SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }

    // Return the vector of subject objects
    return subjects;
}


// Function to create a table for a specific scholar ID and subject code
void DatabaseManager::createSubjectTable(const std::string& scholarID, const std::string& subjectCode) {
    std::stringstream tableName;
    tableName << "table_" << scholarID << "_" << subjectCode;

    std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName.str() + " (date TEXT PRIMARY KEY, present BOOLEAN);";

    char* messageError;
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "\t\t\tError creating subject table: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else {
        std::cout << "\t\t\tSubject table created successfully!" << std::endl;
    }
}