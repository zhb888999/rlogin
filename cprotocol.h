#ifndef CPROTOCOL_H
#define CPROTOCOL_H
#include <inttypes.h>

#define BUFFSIZE 1024
#define TYPE_SZIE 1
#define DATA_SIZE 2


union _head
{
    unsigned char to_char;
    struct {
        unsigned char code:6;
        unsigned char type:2;
    } bits;
};

union _dsize
{
    uint16_t uint16;
    struct 
    {
        uint16_t high:8;
        uint16_t low:8;
    } to_uchar;
};

union _id
{
    uint32_t uint32;
    struct 
    {
        uint64_t uc3:8;
        uint64_t uc2:8;
        uint64_t uc1:8;
        uint64_t uc0:8;
    } to_uchar;
    
};

enum _dtype {CONNECT, CONTENT, INTERRUPT};

typedef union _head  cp_head;
typedef union _dsize  cp_dsize;
typedef union _id  cp_id;
typedef enum _dtype dtype; 

void set_head(cp_head* head, dtype type, uint16_t code);
int set_id(cp_id id, unsigned char* data);
int get_send_data(cp_head head, uint16_t size,const unsigned char* data, unsigned char* buff);
int set_connect_data(unsigned char* buff);

#endif