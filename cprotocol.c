#include <arpa/inet.h>
#include "cprotocol.h"

void set_head(cp_head* head, dtype type, uint16_t code) 
{
    head->bits.type = type;
    head->bits.code = code;
}

int set_id(uint32_t id, unsigned char* data)
{
    cp_id cpid;
    cpid.uint32 = htonl(id);
    *data     = cpid.to_uchar.uc0;
    *(data+1) = cpid.to_uchar.uc1;
    *(data+2) = cpid.to_uchar.uc2;
    *(data+3) = cpid.to_uchar.uc3;
    return 4;
}

int get_send_data(cp_head head, uint16_t size, const unsigned char* data, unsigned char* buff)
{
    cp_dsize dsize;
    dsize.uint16 = htons(size);
    *buff = head.to_char;
    *(buff+1) = dsize.to_uchar.low;
    *(buff+2) = dsize.to_uchar.high;   
    if (data) 
        for(int i=0; i < size; i++) 
            *(buff+3+i) = *(data+i);
    return size+3;
}