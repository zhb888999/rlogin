#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t pid = fork();
    int state = -1;
    if(pid == 0) {
        execlp("bash", "");
        printf(">>>");
    } else {
        wait(&state);
    }
}
