#ifndef FCL_FC_PROXY_H
#define FCL_FC_PROXY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "fcl_types.h"

void fcl_init_fc_proxy(void* ptr, on_fcl_update callback);
void fcl_deinit_fc_proxy();
void fcl_send_to_fc(fclCmd_t cmd, void *data);
bool fcl_get_from_fc(fclCmd_t cmd, void *data);

#ifdef __cplusplus
}
#endif

#endif // FCL_FC_PROXY_H