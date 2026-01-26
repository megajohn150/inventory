#include "singlecharacter.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#elif __APPLE__
#include <TargetConditionals.h>
#include <termios.h>
#include <unistd.h>
#endif

char getSingleChar() {
#ifdef _WIN32
    return _getch();
#elif __APPLE__
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#else
    return 0;
#endif
}
