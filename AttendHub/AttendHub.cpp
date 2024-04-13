// AttendHub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#endif
#include<string.h>
#include"customInput.h"
#include "People.h"
#include "Student.h"
#include <sqlite3.h>
using namespace std;

#ifdef _WIN32
void gotoxy(int x, int y) {
    COORD ord;
    ord.X = x;
    ord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

void clearScreen() {
    system("cls");
}

void effect() {
    int i, j;
    char ch = 220;
    gotoxy(0, 0);
    for (i = 0; i < 25; i++) {
        for (j = 0; j < 125; j++) {
            std::cout << ch;
        }
        Sleep(12);
        std::cout << "\n";
    }
    gotoxy(0, 0);
    for (i = 0; i < 27; i++) {
        std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t            \n";
        Sleep(20);
    }
}
void startScreen() {
    Sleep(800);
    gotoxy(55, 10);
    std::cout << "ATTENDHUB\n";
    Sleep(600);
    system("color 0a");
    gotoxy(52, 12);
    Sleep(1000);
    std::cout << "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
    Sleep(2000);
    std::cout << "\xDB\xDB\xDB\xDB";
    Sleep(1000);
    std::cout << "\xDB\xDB\xDB\xDB\xDB\xDB";
    Sleep(1000);
    std::cout << "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
    Sleep(500);
    system("color a0");
    effect();
}
#else
// Define cross-platform functions for non-Windows systems
void clearScreen() {
    std::cout << string(100, '\n');
}
void startScreen() {
    std::cout << "ATTENDHUB\n";
    std::cout << "LOADING....\n"
    clearScreen();
}
#endif

void StudentMenu(Student& s) { // Pass Student object by reference
    while (true) {
        std::cout << "Student Menu" << std::endl;
        std::cout << "1. View Subjects" << std::endl;
        std::cout << "2. Add Subjects" << std::endl;
        std::cout << "3. Delete Subjects" << std::endl;
        std::cout << "4. Add Attendance" << std::endl;
        std::cout << "5. Edit Attendance" << std::endl;
        std::cout << "6. View Attendance" << std::endl;
        std::cout << "7. View Profile" << std::endl;
        std::cout << "8. Log Out" << std::endl;

        char studentChoice;
        takeInput(&studentChoice);

        switch (studentChoice) {
        case '1':
            // Implement View Subjects functionality
            s.viewSubjects();
            break;
        case '2':
            // Implement Add Subjects functionality
            s.addSubject();
            break;
        case '3':
            // Implement Delete Subjects functionality
            s.deleteSubject();
            break;
        case '4':
            // Implement Add Attendance functionality
            s.addAttendance();
            break;
        case '5':
            // Implement Edit Attendance functionality
            s.editAttendance();
            break;
        case '6':
            // Implement View Attendance functionality
            s.viewAttendance();
            break;
        case '7':
            // Implement View Profile functionality
            s.viewProfile();
            break;
        case '8':
            return; // Log out
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}

void Menu() {
    clearScreen();
    char choice;
    do
    {
        std::cout << "\n\t\t\t\t\t\t  AttendHUB \n";
        std::cout << "\t\t\t\t________________________________________________\n\n";
        std::cout << "\n\t\t\t\t\t\t1 -> Login\n";
        std::cout << "\n\t\t\t\t\t\t2 -> Signup\n";
        std::cout << "\n\t\t\t\t\t(Any other key) -> Exit\n";
        std::cout << "\n\t\t\t||Choose your option (Enter number corressponding to your selection): ";
        takeInput(&choice);
        Student s;
        switch (choice)
        {
        case '1':
            if (s.login()) {
                StudentMenu(s);
            }
            break;
        case '2':
            if (s.signup()) {   
                StudentMenu(s);
            }
            break;
        default:
            std::cout << "Are you sure you want to exit?(Y,N)" << std::endl;
            char c;
            takeInput(&c);
            if (c == 'y' || c == 'Y')
            {
                exit(0);
            }
        }
    } while (true);
}


// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        // column name and value
        cout << azColName[i] << ": " << argv[i] << endl;
    }

    cout << endl;

    return 0;
}
static int selectData(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "SELECT * FROM students;";

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
    exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in selectData function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records selected Successfully!" << endl;

    return 0;
}

int main()
{
    selectData("C:\\Users\\adhik\\OneDrive\\Desktop\\junk\\data.db");
    //Uncomment for an animated start screen
    //startScreen();
    Menu();
}
