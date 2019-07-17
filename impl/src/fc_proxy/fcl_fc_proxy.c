#include "fcl_fc_proxy.h"
#include "fcl_base.h"
#include "fcl_cfg.h"
#include "udplink.h"
#include <string.h>

static fcl_context_t context;
static fcl_motor_t data_motor;

void fcl_init_fc_proxy() {

  memset(&context, 0, sizeof(context));
  context.cmd_buf[eMotor] = &data_motor;
  context.local_addr = NULL;
  context.local_port = FCLINK_FC_PORT;
  context.remote_addr = FCLINK_ADDR;
  context.remote_port = FCLINK_SIM_PORT;
  fcl_init_proxy(&context);
}

void fcl_deinit_fc_proxy() { fcl_deinit_proxy(&context); }

void fcl_send_to_fc(fclCmd_t cmd, void *data) {
  fcl_send_data(&context.link_s, cmd, data);
}

bool fcl_get_from_fc(fclCmd_t cmd, void *data) {
  return fcl_get_data(&context, cmd, data);
}