#include "sim_lib.h"
#include "udplink.h"
#include "fclink.h"
#include <string.h>

static udpLink_t link;

void init_sim_lib()
{
    udpInit(&link, "127.0.0.1", SIM_LIB_PORT, false); 
}

void sim_lib_send(eFccCmd cmd, void* data)
{
    uint8_t tmp[128];
    fcc_header_t* hdr = (fcc_header_t*) tmp;
    hdr->cmd = (uint16_t)cmd;
    hdr->len = (uint16_t)fclink_cmd_len[cmd];
    memcpy(tmp + sizeof(fcc_header_t), data, hdr->len);
    size_t len = sizeof(fcc_header_t) + hdr->len;
    //fcc_parse(tmp, len);
    udpSend(&link, tmp, len);
}