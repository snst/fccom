#include "fcl_base.h"
#include "fcl_types.h"
#include "udplink.h"
#include <string.h>

size_t fcl_cmd_len[eLastCmd] = {sizeof(fcl_sonar_t), sizeof(fcl_pos_t),
                                sizeof(fcl_gps_t),   sizeof(fcl_imu_t),
                                sizeof(fcl_motor_t), sizeof(fcl_joystick_t)};

void fcl_send_data(udpLink_t *link, fclCmd_t cmd, void *data) {

  uint8_t tmp[128];
  fcl_hdr_t *hdr = (fcl_hdr_t *)tmp;
  hdr->cmd = (uint16_t)cmd;
  hdr->len = (uint16_t)fcl_cmd_len[cmd];
  memcpy(tmp + sizeof(fcl_hdr_t), data, hdr->len);
  size_t len = sizeof(fcl_hdr_t) + hdr->len;
  udpSend(link, tmp, len);
}

bool fcl_get_data2(void *cmd_buf[], fclCmd_t cmd, void *data) {

  bool ret = false;
  if (cmd < eLastCmd) {
    void *src = cmd_buf[cmd];
    if (NULL != src) {
      memcpy(data, src, fcl_cmd_len[cmd]);
      ret = true;
    }
  }
  return ret;
}

bool fcl_get_data(fcl_context_t *context, fclCmd_t cmd, void *data) {

  bool ret;
  pthread_mutex_lock(&context->mutex);
  ret = fcl_get_data2(context->cmd_buf, cmd, data);
  pthread_mutex_unlock(&context->mutex);
  return ret;
}

void fcl_set_data(void *cmd_buf[], const char *data, uint32_t len) {

  fcl_hdr_t *hdr = (fcl_hdr_t *)data;
  const char *ptr = data + sizeof(fcl_hdr_t);
  char *dest = NULL;
  if (len == (sizeof(fcl_hdr_t) + hdr->len)) {

    if ((hdr->cmd < eLastCmd) && (hdr->len == fcl_cmd_len[hdr->cmd])) {
      void *dest = cmd_buf[hdr->cmd];
      if (NULL != dest) {
        memcpy(dest, ptr, hdr->len);
      }
    }
  }
}

static void recv_data(void *context, const char *data, uint32_t len) {

  fcl_context_t *ctx = (fcl_context_t *)context;
  pthread_mutex_lock(&ctx->mutex);
  fcl_set_data(ctx->cmd_buf, data, len);
  pthread_mutex_unlock(&ctx->mutex);
}

void fcl_init_proxy(fcl_context_t *context) {

  pthread_mutex_init(&context->mutex, NULL);
  context->link_r.context = context;
  context->link_s.context = context;
  udpInit(&context->link_s, context->remote_addr, context->remote_port, false);
  udpInitRecvThread(&context->link_r, context->local_addr, context->local_port,
                    &recv_data, 100, context->buffer, sizeof(context->buffer));
}

void fcl_deinit_proxy(fcl_context_t *context) {

  udpDeinit(&context->link_s);
  udpDeinit(&context->link_r);
}