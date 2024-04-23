#ifndef PASSWORD_H
#define PASSWORD_H

#include <iostream>
#include <string>
// functional header
// for hash<class template> class
#include <functional>

class Password {
private:
    std::string encryptedPassword;

public:
    Password();

    void getPasswordFromUser();

    std::string getEncryptedPassword() const;
};

#endif // PASSWORD_H
