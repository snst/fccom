#ifndef FCL_SIM_PROXY_H
#define FCL_SIM_PROXY_H

#include <stdint.h>
#include <stdbool.h>
#include "fcl_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void fcl_init_sim_proxy();
void fcl_deinit_sim_proxy();
void fcl_send_to_sim(fclCmd_t cmd, void* data);
bool fcl_get_from_sim(fclCmd_t cmd, void* data);

#ifdef __cplusplus
}
#endif

#endif // FCL_SIM_PROXY_H