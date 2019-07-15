#ifndef FC_LINK_H
#define FC_LINK_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "fcc_hdr.h"
#include "udplink.h"

extern size_t fclink_cmd_len[2];
void fclink_send_data(udpLink_t *link, eFccCmd cmd, void *data);
bool fclink_get_data(void* cmd_buf[], eFccCmd cmd, void* data);
void fclink_set_data(void *cmd_buf[], const char *data, uint32_t len);

#endif // FC_LINK_H