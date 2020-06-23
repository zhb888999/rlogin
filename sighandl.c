#include "sighandl.h"
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

const int* fdm;
char child_is_die = 0;
struct termios tcattr;

void init_signal(const int* fd, const struct termios* attr)
{
    tcattr = *attr;
    fdm = fd;
    signal(SIGWINCH, handl_winch);
    signal(SIGINT, handl_int);
    signal(SIGCHLD, handl_chld);
    signal(SIGTSTP, handl_tstp);
}

void send_code(char code)
{
    write(*fdm, &code, 1);
}

void set_winsize() 
{
    struct winsize size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    ioctl(*fdm, TIOCSWINSZ, &size);
}

void handl_winch(int signo) 
{
    set_winsize();
}

void handl_int(int signo)
{
    if (child_is_die) {
        tcsetattr(STDIN_FILENO, TCSADRAIN, &tcattr);
        exit(0);
    }
    send_code(CODE_INT);
}

void handl_chld(int signo)
{
    child_is_die = 1;
}

void handl_tstp(int signo)
{
    send_code(CODE_TSTP);
}
