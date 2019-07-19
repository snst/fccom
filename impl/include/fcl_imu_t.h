#ifndef FCL_IMU_H
#define FCL_IMU_H

#include <stdint.h>
#include "fcl_hdr_t.h"

typedef struct 
{
    double sim_time;
    double linear_acceleration_x;
    double linear_acceleration_y;
    double linear_acceleration_z;

    double angular_velocity_r;
    double angular_velocity_p;
    double angular_velocity_y;

    double orientation_quat_w;
    double orientation_quat_x;
    double orientation_quat_y;
    double orientation_quat_z;
} fcl_imu_t;

#endif // FCL_IMU_H
