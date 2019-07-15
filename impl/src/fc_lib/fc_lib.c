#include "fc_lib.h"
#include "fclink.h"
#include "sim_lib.h"
#include "udplink.h"
#include <string.h>

static udpLink_t link_s;
static udpLink_t link_r;
static uint8_t buffer[128];
static fcc_sonar_t data_sonar;
static fcc_pos_t data_pos;

void *cmd_buf[] = {&data_sonar, &data_pos};

void recv_data(const char *data, uint32_t len) {

  fclink_set_data(cmd_buf, data, len);
}

void init_fc_lib() {

  udpInit(&link_s, "127.0.0.1", FC_LIB_PORT, false);
  udpInitRecvThread(&link_r, "127.0.0.1", SIM_LIB_PORT, &recv_data, 100, buffer,
                    sizeof(buffer));
}

void fc_send_data(eFccCmd cmd, void *data) {

  fclink_send_data(&link_s, cmd, data);
}

bool sim_get_data(eFccCmd cmd, void *data) {

  return fclink_get_data(cmd_buf, cmd, data);
}