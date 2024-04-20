//#pragma once
#ifndef CUSTOM_INPUT_H
#define CUSTOM_INPUT_H


#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <type_traits>

// Returns true if input is not empty
template <typename DataType>
bool takeInput(DataType* var,bool isSentence=true,bool canBeEmpty=false) {
    while (true) {
        std::string input;
        std::getline(std::cin, input); // Read input as string

        // If not a sentence, extract only the first word
        if (!isSentence) {
            std::istringstream iss(input);
            iss >> input; // Extract first word
        }

        try {
            if (!canBeEmpty && input.empty()) {
                throw std::invalid_argument("Input cannot be empty.");
            }
            
            // Store whether input is empty
            bool isEmpty = input.empty();

            /*constexpr is a keyword in C++ that specifies 
            that an expression can be evaluated at compile time.
            In the context of our code, it's being used to 
            conditionally compile different branches of code 
            based on the type of DataType.*/
            if constexpr (std::is_same_v<DataType, char>) {
                if (isEmpty) {
                    // Return false indicating input is empty
                    return false;
                }
                *var = input[0];
            }
            else if constexpr (std::is_same_v<DataType, std::string>) {
                *var = input;
            }
            else if constexpr (std::is_same_v<DataType, int>) {
                if (isEmpty) {
                    // Return false indicating input is empty
                    return false;
                }
                size_t pos;
                *var = std::stoi(input, &pos);
                if (pos != input.size()) {
                    throw std::invalid_argument("Invalid input.");
                }
            }
            else if constexpr (std::is_same_v<DataType, double>) {
                if (isEmpty) {
                    // Return false indicating input is empty
                    return false;
                }
                size_t pos;
                *var = std::stod(input, &pos);
                if (pos != input.size()) {
                    throw std::invalid_argument("Invalid input.");
                }
            }
            else if constexpr (std::is_same_v<DataType, long>) {
                if (isEmpty) {
                    // Return false indicating input is empty
                    return false;
                }
                size_t pos;
                *var = std::stol(input, &pos);
                if (pos != input.size()) {
                    throw std::invalid_argument("Invalid input.");
                }
            }
            else if constexpr (std::is_same_v<DataType, float>) {
                if (isEmpty) {
                    // Return false indicating input is empty
                    return false;
                }
                size_t pos;
                *var = std::stof(input, &pos);
                if (pos != input.size()) {
                    throw std::invalid_argument("Invalid input.");
                }
            }
            else if constexpr (std::is_same_v<DataType, long long>) {
                if (isEmpty) {
                    // Return false indicating input is empty
                    return false;
                }
                size_t pos;
                *var = std::stoll(input, &pos);
                if (pos != input.size()) {
                    throw std::invalid_argument("Invalid input.");
                }
            }
            else {
                throw std::invalid_argument("Unsupported type.");
            }
            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << ".\nPlease enter again: ";
        }
    }
}



#endif
