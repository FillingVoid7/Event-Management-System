#include "PasswordField.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>  

PasswordField::PasswordField(int length) : placeholderLength(length) {}

std::string PasswordField::getMaskedInput() {
    std::string result;
    char ch;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n') { 
        if (ch == 127 || ch == '\b') { 
            if (!result.empty()) {
                result.pop_back();
                std::cout << "\b \b"; 
            }

        } else {
            result += ch;
            std::cout << '*'; // Mask character
        }
    }
    std::cout << std::endl;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore settings

    return result;
}

std::string PasswordField::getline() {
    std::cout << "Enter Password: ";
    std::string input = getMaskedInput();
    return getMaskedInput();
}
