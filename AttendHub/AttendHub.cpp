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
#include "Student.h"
#include "DatabaseManager.h"
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
        std::cout << "8. Edit Profile" << std::endl;
        std::cout << "9. Change Password" << std::endl;
        std::cout << "10. Log Out" << std::endl;

        char studentChoice;
        takeInput(&studentChoice);

        switch (studentChoice) {
        case '1':
            s.viewSubjects();
            break;
        case '2':
            s.addSubject();
            break;
        case '3':
            s.deleteSubject();
            break;
        case '4':
            s.addAttendance();
            break;
        case '5':
            s.editAttendance();
            break;
        case '6':
            s.viewAttendance();
            break;
        case '7':
            s.viewProfile();
            break;
        case '8':
            //s.editProfile();
            break;
        case '9':
            s.changePassword();
            break;
        case '10':
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
        std::cout << "\n\t\t\t\t\t\t3 -> Forgot Password\n";
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
        case '3':
            if (s.forgotPassword()) {
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



int main()
{
    //Uncomment for an animated start screen
    //startScreen();
    Menu();
}
