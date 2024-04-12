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
#include "AttendHub.h"

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


// Will be implementing in upcoming versions:
//void Admin() {
//    while (true)
//    {
//        std::cout << "Admin Mode" << std::endl;
//        std::cout << "1. Login" << std::endl;
//        std::cout << "2. Signup" << std::endl;
//        std::cout << "3. Add class" << std::endl;
//        std::cout << "4. Assign teacher" << std::endl;
//        std::cout << "5. Show Profile" << std::endl;
//        std::cout << "6. LogOut" << std::endl;
//        char adminChoice;
//        takeInput(&adminChoice);
//        switch (adminChoice) {
//        case '1':
//            // Implement Login functionality
//            break;
//        case '2':
//            // Implement Signup functionality
//            break;
//        case '3':
//            // Implement Add class functionality
//            break;
//        case '4':
//            // Implement Assign teacher functionality
//            break;
//        case '5':
//            // Implement Show Profile functionality
//            break;
//        case '6':
//            return; // Log out
//        default:
//            std::cout << "Invalid choice. Please try again." << std::endl;
//            break;
//        }
//    }
//}
//
//
//
//void Instructor() {
//    while (true) {
//        std::cout << "Instructor Mode" << std::endl;
//        std::cout << "1. Login" << std::endl;
//        std::cout << "2. Signup" << std::endl;
//        std::cout << "3. Take attendance" << std::endl;
//        std::cout << "2. View class schedule" << std::endl;
//        std::cout << "3. Grade assignments" << std::endl;
//        std::cout << "4. Show Profile" << std::endl;
//        std::cout << "5. LogOut" << std::endl;
//        char instructorChoice;
//        takeInput(&instructorChoice);
//        switch (instructorChoice) {
//        case '1':
//            // Implement Take attendance functionality
//            break;
//        case '2':
//            // Implement View class schedule functionality
//            break;
//        case '3':
//            // Implement Grade assignments functionality
//            break;
//        case '4':
//            // Implement Show Profile functionality
//            break;
//        case '5':
//            return; // Log out
//        default:
//            std::cout << "Invalid choice. Please try again." << std::endl;
//            break;
//        }
//    }
//}
void Menu() {
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
                std::cout << "Login Successfull!!\n";
                StudentMenu(s);
            }
            else {
                std::cout << "Login Unsuccessfull!!\n";
            }
            break;
        case '2':
            if (s.signup()) {
                std::cout << "Signup Successfull!!\n";
                StudentMenu(s);
            }
            else {
                std::cout << "Signup Unsuccessfull!!\n";
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


int main()
{
    //Uncomment for an animated start screen
    //startScreen();
    Menu();



    // Will implement in upcomming versions:
    //char choice;
    //do
    //{
    //    //clearScreen();

    //    std::cout << "\n\t\t\t\t\t\t  AttendHUB \n";
    //    std::cout << "\t\t\t\t________________________________________________\n\n";
    //    std::cout << "\n\t\t\t\t\t\t1 -> Admin\n";
    //    std::cout << "\n\t\t\t\t\t\t2 -> Instructor\n";
    //    std::cout << "\n\t\t\t\t\t\t3 -> Student\n";

    //    //std::cout << "\n\t\t\t\t\t\t6. About Developers\n";
    //    std::cout << "\n\t\t\t\t\t(Any other key) -> Exit\n";
    //    std::cout << "\n\t\t\t||Choose your option (Enter number corressponding to your selection): ;
    //    takeInput(&choice);
    //    switch (choice)
    //    {
    //    case '1':
    //        Admin();
    //        break;
    //    case '2':
    //        Instructor();
    //        break;
    //    case '3':
    //        Student();
    //        break;
    //    default:
    //        std::cout << "Are you sure you want to exit?(Y,N)" << std::endl;
    //        char c;
    //        takeInput(&c);
    //        if (c == 'y' || c == 'Y')
    //        {
    //            exit(0);
    //        }
    //    }
    //} while (true);
}
