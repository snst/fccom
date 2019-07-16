#include "fcl_base.h"
#include "fcl_pos.h"
#include "fcl_sonar.h"
#include "udplink.h"
#include <string.h>

size_t fcl_cmd_len[] = {sizeof(fcl_sonar_t), sizeof(fcl_pos_t)};

void fcl_send_data(udpLink_t *link, fclCmd_t cmd, void *data) {

  uint8_t tmp[128];
  fcl_hdr_t *hdr = (fcl_hdr_t *)tmp;
  hdr->cmd = (uint16_t)cmd;
  hdr->len = (uint16_t)fcl_cmd_len[cmd];
  memcpy(tmp + sizeof(fcl_hdr_t), data, hdr->len);
  size_t len = sizeof(fcl_hdr_t) + hdr->len;
  udpSend(link, tmp, len);
}

bool fcl_get_data(void *cmd_buf[], fclCmd_t cmd, void *data) {

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