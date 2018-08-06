#ifndef BITSYBS_INTERNAL_H

#include <stdint.h>

struct bfnode
{
    uint32_t used;
    struct bfnode *first;
    struct bfnode *next;
    char name[32];
    uint32_t crc;
    uint16_t size;
    char *data;
};

#endif