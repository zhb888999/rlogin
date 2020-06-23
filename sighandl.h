#ifndef SIGHANDL_H
#define SIGHANDL_H

#include <sys/ioctl.h>
#include <termios.h>

#define CODE_INT 3
#define CODE_TSTP 26

extern void init_signal(const int* fd, const struct termios* attr);
extern void set_winsize();
extern void send_code(char code);
extern void handl_winch(int signo);
extern void handl_int(int signo);
extern void handl_chld(int signo);
extern void handl_tstp(int signo);

#endif
