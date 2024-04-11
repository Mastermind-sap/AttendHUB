//#pragma once
//#ifndef CUSTOM_INPUT_H
//#define CUSTOM_INPUT_H
//
//#include <iostream>
//#include <limits>
//#include <stdexcept>
//
//template <typename DataType>
//void takeInput(DataType* var) {
//    while (true) {
//        try {
//            // Input data from standard input
//            if (!(std::cin >> *var)) {
//                // Clear the failbit
//                std::cin.clear();
//
//                // Discard any remaining characters in the input buffer
//                while (std::cin.get() != '\n') {
//                    continue;
//                }
//
//                throw std::invalid_argument("Invalid input.");
//            }
//
//            // If extraction was successful, break out of the loop
//            break;
//        }
//        catch (const std::exception& e) {
//            std::cerr << "\n" << e.what() << "\n";
//            std::cout << "Enter again:";
//        }
//    }
//}
//#endif

#pragma once
#ifndef CUSTOM_INPUT_H
#define CUSTOM_INPUT_H

#include<iostream>
#include<limits>
#include <stdexcept>

template <typename DataType>
void takeInput(DataType* var) {
    while (true) {
            std::cin >> var;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                std::cout << "Invalid input" << endl;
                std::cout << "Enter again:";

            }
            if (!cin.fail())
                break;
    }
}

#endif

