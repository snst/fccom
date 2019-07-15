#ifndef SIM_LIB_H
#define SIM_LIB_H

#include <stdint.h>
#include "fcc_sonar.h"
#include "fcc_pos.h"

#define SIM_LIB_PORT 44444

#ifdef __cplusplus
extern "C" {
#endif

void init_sim_lib();
void sim_lib_send(eFccCmd cmd, void* data);

#ifdef __cplusplus
}
#endif

#endif // SIM_LIB_H