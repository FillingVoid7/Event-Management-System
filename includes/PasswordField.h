#ifndef PASSWORDFIELD_H
#define PASSWORDFIELD_H

#include <string>

class PasswordField {
private:
    const int placeholderLength;
    
    std::string getMaskedInput();

public:
    PasswordField(int length);
    std::string getline();
};

#endif // PASSWORDFIELD_H
