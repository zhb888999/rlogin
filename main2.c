#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void run()
{
    printf(">>>>>\n");
}
int main()
{
    signal(SIGWINCH, run);
    for(;;) {
        sleep(1);
    }
}
