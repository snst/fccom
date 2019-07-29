#ifndef FCL_FCSTATE_H
#define FCL_FCSTATE_H

#include <stdint.h>
#include "fcl_imu_t.h"
#include "fcl_pos_t.h"

typedef struct
{
    double sim_time;
    fcl_imu_t imu;
    fcl_pos_t pos;
} fcl_fcstate_t;


#endif // FCL_FCSTATE_H
