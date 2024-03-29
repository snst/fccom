#include "fcl_fc_proxy.h"
#include "fcl_base.h"
#include "fcl_cfg.h"
#include "udplink.h"
#include <string.h>

static fcl_context_t context;
static fcl_motor_t data_motor;
static fcl_resetworld_t data_resetworld;

void fcl_init_fc_proxy(void* ptr, on_fcl_update callback) {

  memset(&context, 0, sizeof(context));
  context.data_callback = callback;
  context.data_callback_ptr = ptr;
  context.cmd_buf[eMotor] = &data_motor;
  context.cmd_buf[eResetWorld] = &data_resetworld;
  context.local_addr = NULL;
  context.local_port = FCL_SIM_PORT;
  context.remote_addr = FCL_FC_ADDR;
  context.remote_port = FCL_FC_PORT;
  fcl_init_proxy(&context);
}

void fcl_deinit_fc_proxy() { fcl_deinit_proxy(&context); }

void fcl_send_to_fc(fclCmd_t cmd, void *data) {
  fcl_send_data(&context.link_s, cmd, data);
}

bool fcl_get_from_fc(fclCmd_t cmd, void *data) {
  return fcl_get_data(&context, cmd, data);
}