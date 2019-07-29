#ifndef FCL_JOYSTICK_H
#define FCL_JOYSTICK_H

#include <stdint.h>
#include "fcl_hdr_t.h"

#define MAX_JOYSTICK_AXES (5u)
#define MAX_RC_CHANNELS (5u)

typedef struct
{
    float val[MAX_RC_CHANNELS];
    //uint16_t axis[MAX_JOYSTICK_AXES];
    uint16_t button;
} fcl_joystick_t;

#endif // FCL_JOYSTICK_H