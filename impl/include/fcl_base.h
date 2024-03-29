#ifndef FCL_BASE_H
#define FCL_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fcl_types.h"
#include "udplink.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


typedef struct {
  pthread_mutex_t mutex;
  udpLink_t link_s;
  udpLink_t link_r;
  void *cmd_buf[eLastCmd];
  uint8_t buffer[128];
  uint16_t local_port;
  uint16_t remote_port;
  const char* local_addr;
  const char* remote_addr;
  on_fcl_update data_callback;
  void* data_callback_ptr;
} fcl_context_t;

extern size_t fcl_cmd_len[eLastCmd];


void fcl_send_data(udpLink_t *link, fclCmd_t cmd, void *data);
bool fcl_get_data(fcl_context_t* context, fclCmd_t cmd, void *data);
fclCmd_t fcl_set_data(void *cmd_buf[], const char *data, uint32_t len);
bool fcl_get_data2(void *cmd_buf[], fclCmd_t cmd, void *data);
void fcl_init_proxy(fcl_context_t* context);
void fcl_deinit_proxy(fcl_context_t* context);

#ifdef __cplusplus
}
#endif

#endif // FCL_BASE_H