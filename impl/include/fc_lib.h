#ifndef FC_LIB_H
#define FC_LIB_H

#include <stdint.h>
#include <stdbool.h>
#include "fcc_sonar.h"
#include "fcc_pos.h"

#define FC_LIB_PORT 44445

#ifdef __cplusplus
extern "C" {
#endif

void init_fc_lib();
void fc_send_data(eFccCmd cmd, void* data);
bool sim_get_data(eFccCmd cmd, void* data);

#ifdef __cplusplus
}
#endif

#endif // FC_LIB_H