#ifndef FCL_MOTOR_H
#define FCL_MOTOR_H

#include <stdint.h>
#include "fcl_hdr_t.h"

#define MAX_MOTORS (4u)

typedef struct
{
    float motor[MAX_MOTORS];
} fcl_motor_t;

#endif // FCL_MOTOR_H