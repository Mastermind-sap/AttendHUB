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



void Admin() {
    std::cout << "Admin" << std::endl;
    People p;
    p.signup();
    p.showDetails();
    //clearScreen();
}



int main()
{
    //Uncomment for an animated start screen
    //startScreen();
    char choice;
    do
    {
        //clearScreen();

        std::cout << "\n\t\t\t\t\t\t  AttendHUB \n";
        std::cout << "\t\t\t\t________________________________________________\n\n";
        std::cout << "\n\t\t\t\t\t\t1 -> Admin\n";
        std::cout << "\n\t\t\t\t\t\t2 -> Instructor\n";
        std::cout << "\n\t\t\t\t\t\t3 -> Student\n";

        //std::cout << "\n\t\t\t\t\t\t6. About Developers\n";
        std::cout << "\n\t\t\t\t\t(Any other key) -> Exit\n";
        std::cout << "\n\t\t\t||Choose your option (Enter number corressponding to your selection): ";
        //choice = getchar();
        takeInput(&choice);
        switch (choice)
        {
        case '1':
            Admin();
            break;
        case '2':
            std::cout << "Instructor" << std::endl;
            clearScreen();
            break;
        case '3':
            std::cout << "Student" << std::endl;
            clearScreen();
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
