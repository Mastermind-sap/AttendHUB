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

//#ifndef CUSTOM_INPUT_H
//#define CUSTOM_INPUT_H

//#include<iostream>
//#include<limits>
//#include <stdexcept>
//#define NOMINMAX
//#include <windows.h>
//
//template <typename DataType>
//void takeInput(DataType* var) {
//    while (true) {
//            std::cin >> var;
//            if (std::cin.fail())
//            {
//                std::cin.clear();
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                std::cout << "Invalid input" << std::endl;
//                std::cout << "Enter again:";
//
//            }
//            if (!std::cin.fail())
//                break;
//    }
//}
//
//#endif





#pragma once
#ifndef CUSTOM_INPUT_H
#define CUSTOM_INPUT_H

#include <iostream>
#include <sstream>
#include <limits>
#include <stdexcept>

template <typename DataType>
void takeInput(DataType* var, bool isSentence = true) {
    while (true) {
        try {
            std::string input;
            std::getline(std::cin, input); // Read input as string

            std::stringstream iss(input);

            if (isSentence && std::is_same_v<DataType, std::string>) {
                *var = ""; // Initialize var to an empty string
                std::string word;
                while (iss >> word) {
                    *var =*var+ word + " "; // Append each word to the string
                }
                *var = var->substr(0, var->size() - 1); // Remove the extra space at the end
            }
            else {
                if (!(iss >> *var)) { // Try to convert string to DataType
                    throw std::invalid_argument("Invalid input.");
                }
            }
            return; // If conversion was successful and no extra characters are left, break out of the loop
        }
        catch (const std::exception& e) {
            std::cerr << "Invalid input. Please enter again: ";
        }
    }
}

//#include <iostream>
//#include <string> // Add this line
//#include <sstream>
//#include <limits>
//#include <stdexcept>
//#include <type_traits>
//#include <any>
//
//template <typename DataType>
//void takeInput(DataType* var) {
//    while (true) {
//        try {
//            std::string input;
//            std::getline(std::cin, input); // Read input as string
//            std::any a = input;
//            *var = any_cast<DataType>(a);
//            /*if constexpr (std::is_same_v<DataType, char>) {
//                *var = input[0];
//            }
//            else if constexpr (std::is_same_v<DataType, std::string>) {
//                *var = input;
//            }
//            else if constexpr (std::is_same_v<DataType, int>) {
//                *var = std::stoi(input);
//            }
//            else {
//                *var = (DataType)input;
//            }*/
//            return;
//        }
//        catch (boost::bad_any_cast& e)
//        {
//            std::cerr << e.what() << '\n';
//        }
//
//    }
//}



#endif
