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

void printAttendHUB() {
    std::cout << "\t\t\t\t  +==========================================================+" << std::endl;
    std::cout << "\t\t\t\t  |                                                          |" << std::endl;
    std::cout << "\t\t\t\t  |                                                          |" << std::endl;
    std::cout << "\t\t\t\t  |                                                          |" << std::endl;
    std::cout << "\t\t\t\t  |                                                          |" << std::endl;
    std::cout << "\t\t\t\t  |        _   _   _                 _ _   _ _   _ ____      |" << std::endl;
    std::cout << "\t\t\t\t  |       / \\ | |_| |_ ___ _ __   __| | | | | | | | __ )     |" << std::endl;
    std::cout << "\t\t\t\t  |      / _ \\| __| __/ _ \\ '_ \\ / _` | |_| | | | |  _ \\     |" << std::endl;
    std::cout << "\t\t\t\t  |     / ___ \\ |_| ||  __/ | | | (_| |  _  | |_| | |_) |    |" << std::endl;
    std::cout << "\t\t\t\t  |    /_/   \\_\\__|\\__\\___|_| |_|\\__,_|_| |_|\\___/|____/     |" << std::endl;
    std::cout << "\t\t\t\t  |                                                          |" << std::endl;
    std::cout << "\t\t\t\t  |                                                          |" << std::endl;
    std::cout << "\t\t\t\t  |                                                          |" << std::endl;
    std::cout << "\t\t\t\t  |                                                          |" << std::endl;
    std::cout << "\t\t\t\t  +==========================================================+" << std::endl;
}

void StudentMenu(Student& s) { // Pass Student object by reference
    while (true) {
        std::cout << "\t\t\t\t\t\t  +-----------------------------+\n";
        std::cout << "\t\t\t\t\t\t  |         Student Menu        |\n";
        std::cout << "\t\t\t\t\t\t  +-----------------------------+\n";
        std::cout << "\t\t\t\t\t\t  | 1. View Subjects            |\n";
        std::cout << "\t\t\t\t\t\t  | 2. Add Subjects             |\n";
        std::cout << "\t\t\t\t\t\t  | 3. Edit Subjects            |\n";
        std::cout << "\t\t\t\t\t\t  | 4. Delete Subjects          |\n";
        std::cout << "\t\t\t\t\t\t  | 5. Add Attendance           |\n";
        std::cout << "\t\t\t\t\t\t  | 6. Edit Attendance          |\n";
        std::cout << "\t\t\t\t\t\t  | 7. View Attendance          |\n";
        std::cout << "\t\t\t\t\t\t  | 8. View Profile             |\n";
        std::cout << "\t\t\t\t\t\t  | 9. Edit Profile             |\n";
        std::cout << "\t\t\t\t\t\t  | A. Change Password          |\n";
        std::cout << "\t\t\t\t\t\t  | Q. Log Out                  |\n";
        std::cout << "\t\t\t\t\t\t  +-----------------------------+\n";
        std::cout << "\n\t\t\t|| Choose your option (Enter number corresponding to your selection): "; 
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
            s.editSubject();
            break;
        case '4':
            s.deleteSubject();
            break;
        case '5':
            s.addAttendance();
            break;
        case '6':
            s.editAttendance();
            break;
        case '7':
            s.viewAttendance();
            break;
        case '8':
            s.viewProfile();
            break;
        case '9':
            //s.editProfile();
            break;
        case 'A':
            s.changePassword();
            break;
        case 'Q':
            clearScreen(); //clears any confidential data that is on screen
            return; // Log out
        default:
            std::cout << "\n\t\t\tInvalid choice. Please try again." << std::endl;
            break;
        }
    }
}

void Menu() {
    clearScreen();
    printAttendHUB();
    char choice;
    do
    {
        std::cout << "\n\t\t\t\t\t\t  +-----------------------------+\n";
        std::cout << "\t\t\t\t\t\t  |             Menu            |\n";
        std::cout << "\t\t\t\t\t\t  +-----------------------------+\n";
        std::cout << "\t\t\t\t\t\t  | 1 -> Login                  |\n";
        std::cout << "\t\t\t\t\t\t  |                             |\n";
        std::cout << "\t\t\t\t\t\t  | 2 -> Signup                 |\n";
        std::cout << "\t\t\t\t\t\t  |                             |\n";
        std::cout << "\t\t\t\t\t\t  | 3 -> Forgot Password        |\n";
        std::cout << "\t\t\t\t\t\t  |                             |\n";
        std::cout << "\t\t\t\t\t\t  | (Any other key) -> Exit     |\n";
        std::cout << "\t\t\t\t\t\t  |                             |\n";
        std::cout << "\t\t\t\t\t\t  +-----------------------------+\n";
        std::cout << "\t\t\t|| Choose your option (Enter number corresponding to your selection): "; 
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
            std::cout << "\n\t\t\tAre you sure you want to exit?(Y,N)" << std::endl;
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
