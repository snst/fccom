#ifndef FCL_TYPES_H
#define FCL_TYPES_H

#include "fcl_sonar.h"
#include "fcl_gps.h"
#include "fcl_pos.h"
#include "fcl_imu.h"

typedef enum
{
    eSonar = 0,
    ePos,
    eGps,
    eImu,
    eLastCmd
} fclCmd_t;


#endif // FCL_TYPES_H
