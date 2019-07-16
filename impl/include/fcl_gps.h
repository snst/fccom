#ifndef FCL_GPS_H
#define FCL_GPS_H

#include <stdint.h>
#include "fcl_hdr.h"

typedef struct
{
    double longitude;
    double latitude;
    double altitude;
    int8_t status;
    uint8_t satellites;
} fcl_gps_t;

#endif // FCL_GPS_H
