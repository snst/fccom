#include "fcl_sim_proxy.h"
#include "fcl_base.h"
#include "fcl_cfg.h"
#include "udplink.h"
#include <string.h>

static fcl_sonar_t data_sonar;
static fcl_pos_t data_pos;
static fcl_gps_t data_gps;
static fcl_imu_t data_imu;
static fcl_joystick_t data_joystick;

static fcl_context_t context;

void fcl_init_sim_proxy(on_fcl_update callback) {

  memset(&context, 0, sizeof(context));
  context.data_callback = callback;
  context.cmd_buf[eSonar] = &data_sonar;
  context.cmd_buf[ePos] = &data_pos;
  context.cmd_buf[eGps] = &data_gps;
  context.cmd_buf[eImu] = &data_imu;
  context.cmd_buf[eJoystick] = &data_joystick;

  context.local_addr = NULL;
  context.local_port = FCL_FC_PORT;
  context.remote_addr = FCL_FC_ADDR;
  context.remote_port = FCL_SIM_PORT;
  fcl_init_proxy(&context);
}

void fcl_deinit_sim_proxy() { fcl_deinit_proxy(&context); }

void fcl_send_to_sim(fclCmd_t cmd, void *data) {
  fcl_send_data(&context.link_s, cmd, data);
}

bool fcl_get_from_sim(fclCmd_t cmd, void *data) {
  return fcl_get_data(&context, cmd, data);
}