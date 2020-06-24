#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "cprotocol.h"

int main()
{
    cp_dsize size, size2;
    size.uint16 = htons(65533);
    size2.uint16 = ntohs(size.uint16);
    printf("%x %x %x\n",size2.uint16, size.to_uchar.low, size.to_uchar.high);
    uint16_t t = htons(65533);
    unsigned char* b;
    b = (unsigned char*)&t;
    printf("%x %x %x\n",t, *b, *(b+1));
}
