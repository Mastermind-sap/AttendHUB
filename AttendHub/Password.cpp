#include "Password.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

Password::Password() : encryptedPassword("") {}

void Password::getPasswordFromUser() {
    std::string password;
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_ECHO_INPUT;
    SetConsoleMode(hStdin, mode);
#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;
    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif

    std::getline(std::cin, password);

#ifdef _WIN32
    mode |= ENABLE_ECHO_INPUT;
    SetConsoleMode(hStdin, mode);
#else
    tty.c_lflag |= ECHO;
    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif

    // Instantiation of Object
    std::hash<std::string> mystdhash;
    // Encrypt the password before storing
    encryptedPassword = mystdhash(password);
}

std::string Password::getEncryptedPassword() const {
    return encryptedPassword;
}
