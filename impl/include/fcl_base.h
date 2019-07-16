#ifndef FCL_BASE_H
#define FCL_BASE_H

#include "fcl_types.h"
#include "udplink.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  udpLink_t link_s;
  udpLink_t link_r;
  void *cmd_buf[eLastCmd];
  uint8_t buffer[128];
  uint16_t local_port;
  uint16_t remote_port;
  const char* local_addr;
  const char* remote_addr;
} fcl_context_t;

extern size_t fcl_cmd_len[eLastCmd];
void fcl_send_data(udpLink_t *link, fclCmd_t cmd, void *data);
bool fcl_get_data(fcl_context_t* context, fclCmd_t cmd, void *data);
void fcl_set_data(void *cmd_buf[], const char *data, uint32_t len);
void fcl_init_proxy(fcl_context_t* context);
void fcl_deinit_proxy(fcl_context_t* context);

#endif // FCL_BASE_H