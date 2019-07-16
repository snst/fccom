#ifndef FCL_BASE_H
#define FCL_BASE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "fcl_hdr.h"
#include "udplink.h"

extern size_t fcl_cmd_len[2];
void fcl_send_data(udpLink_t *link, fclCmd_t cmd, void *data);
bool fcl_get_data(void* cmd_buf[], fclCmd_t cmd, void* data);
void fcl_set_data(void *cmd_buf[], const char *data, uint32_t len);

#endif // FCL_BASE_H