#include <stdint.h>
#include <string.h>
#include "fcc_sonar.h"
#include "fcc_pos.h"

size_t cmds[] = {
    sizeof(fcc_sonar_t),
    sizeof(fcc_pos_t)
};

void fcc_parse(void* data, size_t len);

void fcc_send(eFccCmd cmd, void* data)
{
    uint8_t tmp[128];
    fcc_header_t* hdr = (fcc_header_t*) tmp;
    hdr->cmd = (uint16_t)cmd;
    hdr->len = (uint16_t)cmds[cmd];
    memcpy(tmp + sizeof(fcc_header_t), data, hdr->len);
    size_t len = sizeof(fcc_header_t) + hdr->len;
    fcc_parse(tmp, len);
}

void fcc_parse(void* data, size_t len)
{
    fcc_header_t* hdr = (fcc_header_t*) data;
    if (len == (sizeof(fcc_header_t) + hdr->len)) {
    switch (hdr->cmd) {
        case eSonar:
        break;
        case ePos:
        break;
        default:
        break;
    }
    }
}

int main(int argc, char* argv[])
{
    fcc_sonar_t sonar;
    fcc_pos_t pos;
    fcc_send(eSonar, &sonar);
    fcc_send(ePos, &pos);

    return 0;
}