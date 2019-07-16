#include "fcl_sim_proxy.h"
#include "fcl_base.h"
#include "fcl_cfg.h"
#include "udplink.h"
#include <string.h>

static udpLink_t link_s;
static udpLink_t link_r;
static uint8_t buffer[128];
static fcl_sonar_t data_sonar;
static fcl_pos_t data_pos;
static void *cmd_buf[] = {&data_sonar, &data_pos};

static void recv_data(const char *data, uint32_t len) {

  fcl_set_data(cmd_buf, data, len);
}

void fcl_init_sim_proxy() {

  udpInit(&link_s, FCLINK_ADDR, FCLINK_SIM_PORT, false);
  udpInitRecvThread(&link_r, FCLINK_ADDR, FCLINK_FC_PORT, &recv_data, 100, buffer,
                    sizeof(buffer));
}

void fcl_deinit_sim_proxy() {
  udpDeinit(&link_s);
  udpDeinit(&link_r);
}

void fcl_send_to_sim(fclCmd_t cmd, void *data) {

  fcl_send_data(&link_s, cmd, data);
}

bool fcl_get_from_sim(fclCmd_t cmd, void *data) {

  return fcl_get_data(cmd_buf, cmd, data);
}