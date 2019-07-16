#ifndef FCL_HDR_H
#define FCL_HDR_H

#include <stdint.h>

typedef struct
{
    uint16_t cmd;
    uint16_t len;
} fcl_hdr_t;

typedef enum
{
    eSonar = 0,
    ePos,
    eLastCmd
} fclCmd_t;

#endif // FCL_HDR_H