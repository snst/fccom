#ifndef FCL_TYPES_H
#define FCL_TYPES_H

#include "fcl_sonar_t.h"
#include "fcl_gps_t.h"
#include "fcl_pos_t.h"
#include "fcl_imu_t.h"
#include "fcl_motor_t.h"
#include "fcl_joystick_t.h"

typedef enum
{
    eSonar = 0,
    ePos,
    eGps,
    eImu,
    eMotor,
    eJoystick,
    eLastCmd
} fclCmd_t;

typedef void (*on_fcl_update)(fclCmd_t data);


#endif // FCL_TYPES_H
