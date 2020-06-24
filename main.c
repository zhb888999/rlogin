#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pty.h>
#include <pthread.h>
#include <termios.h>
#include <sys/types.h>
#include "sighandl.h"
#include "client.h"

#define BUFFSIZE 1024


void* cin(void* arg);
void* cout(void* arg);

int main(int argc, char** argv) 
{
    char   ptyname[20];
    pid_t  pid;
    int    fdm, sockfd;
    struct winsize size;
    struct termios tcattr;
    sockfd = client("127.0.0.1", 8000);
    pid = forkpty(&fdm, ptyname, NULL, NULL);

    if (pid == 0) {             /* child */
        execlp("bash", NULL);
    } else {                    /* parent */
        tcgetattr(STDIN_FILENO, &tcattr);
        init_signal(&fdm, &tcattr);

        tcattr.c_lflag &= ~ECHO & ~ICANON;
        tcsetattr(STDIN_FILENO, TCSADRAIN, &tcattr);

        pthread_t pcin, pcout;
        pthread_create(&pcin, NULL, (void*)cin, &fdm);
        pthread_create(&pcout, NULL, (void*)cout, &fdm);
        pthread_join(pcin, NULL);
        pthread_join(pcout, NULL);
    }
}

void* cin(void* arg)
{
    char buff[BUFFSIZE];
    int n;
    int fdm = *(int*)arg;
    for(;;) {
        if((n = read(STDIN_FILENO, buff, BUFFSIZE)) > 0) {
            write(fdm, buff, n);
        }
    }
}

void* cout(void* arg)
{
    char buff[BUFFSIZE];
    int n;
    int fdm = *(int*)arg;
    for(;;) {
        if((n = read(fdm, buff, BUFFSIZE)) > 0)
            write(STDOUT_FILENO, buff, n);
    }
}
