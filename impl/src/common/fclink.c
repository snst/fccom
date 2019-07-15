#include "fclink.h"
#include "fcc_pos.h"
#include "fcc_sonar.h"
#include "udplink.h"

size_t fclink_cmd_len[] = {sizeof(fcc_sonar_t), sizeof(fcc_pos_t)};

void fclink_send_data(udpLink_t *link, eFccCmd cmd, void *data) {

  uint8_t tmp[128];
  fcc_header_t *hdr = (fcc_header_t *)tmp;
  hdr->cmd = (uint16_t)cmd;
  hdr->len = (uint16_t)fclink_cmd_len[cmd];
  memcpy(tmp + sizeof(fcc_header_t), data, hdr->len);
  size_t len = sizeof(fcc_header_t) + hdr->len;
  udpSend(link, tmp, len);
}

bool fclink_get_data(void *cmd_buf[], eFccCmd cmd, void *data) {

  bool ret = false;
  if (cmd < eLastCmd) {
    void *src = cmd_buf[cmd];
    if (NULL != src) {
      memcpy(data, src, fclink_cmd_len[cmd]);
      ret = true;
    }
  }
  return ret;
}

void fclink_set_data(void *cmd_buf[], const char *data, uint32_t len) {

  fcc_header_t *hdr = (fcc_header_t *)data;
  const char *ptr = data + sizeof(fcc_header_t);
  char *dest = NULL;
  if (len == (sizeof(fcc_header_t) + hdr->len)) {

    if ((hdr->cmd < eLastCmd) && (hdr->len == fclink_cmd_len[hdr->cmd])) {
      void *dest = cmd_buf[hdr->cmd];
      if (NULL != dest) {
        memcpy(dest, ptr, hdr->len);
      }
    }
  }
}