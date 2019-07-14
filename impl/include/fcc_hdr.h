#ifndef MSG_COMMON_H
#define MSG_COMMON_H

#include <stdint.h>

typedef struct fcc_header
{
    uint16_t cmd;
    uint16_t len;
} fcc_header_t;

typedef enum fccCmd
{
    eSonar = 0,
    ePos
} eFccCmd;

#endif // MSG_COMMON_H