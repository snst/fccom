// Written by Stefan Schmidt 2019
#include <stdio.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <boost/exception/all.hpp>
#include <exception>
#include "fcl_types.h"
#include "udplink.h"
#include "fcl_cfg.h"
#include "fcl_base.h"

#define RC_UPDATE_SLEEP_MS (10u)

void *cmd_buf[eLastCmd];

static void recv_data(void *context, const char *data, uint32_t len)
{
    static uint32_t i = 0;
    fcl_joystick_t j = {0};
    fcl_set_data(cmd_buf, data, len);
    if (fcl_get_data2(cmd_buf, eJoystick, &j))
    {
        printf("%u r: %u, %u %u %u %u %u, %u\n", i++, len, j.axis[0], j.axis[1], j.axis[2], j.axis[3], j.axis[4], j.button);
    }
}

int main(int argc, char *argv[])
{
    udpLink_t link;
    fcl_joystick_t j = {0};
    char buffer[128];
    cmd_buf[eJoystick] = &j;

    udpInitRecvThread(&link, NULL, FCL_FC_PORT, &recv_data,
                      100, buffer, sizeof(buffer));

    while (true)
    {
        sleep(1);
    }
    return 0;
}