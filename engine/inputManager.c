#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

#include "engine.h"

void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag |= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/* Non-blocking input function. If there is no user input, it returnes '\0' */
char GetInput() {
    fd_set rfds;
    struct timeval tv;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    if(select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv))
        return getchar();
    return '\0';
}