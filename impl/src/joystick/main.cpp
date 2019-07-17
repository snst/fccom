// Written by Stefan Schmidt 2019

// use jstest-gtk
// jscal -t /dev/input/js0
// sudo jscal-store /dev/input/js0
// jscal-restore
// /var/lib/joystick/joystick.state

#include <stdio.h>
#include "Joystick.h"
#include <thread>
#include <iostream>
#include <unistd.h>
#include <boost/exception/all.hpp>
#include <exception>
#include "fcl_types.h"
#include "udplink.h"
#include "fcl_cfg.h"
#include "fcl_base.h"

#define JOYSTICK_DEVICE "/dev/input/js0"
#define RC_UPDATE_SLEEP_MS 20

void joystick_thread(Joystick *js, bool debug)
{
    printf("axis: %i, buttons: %i\n", js->get_axis_count(), js->get_button_count());
    while (js->update())
    {
        if (debug)
        {
            js->print_state();
        }
    }
}

int main(int argc, char *argv[])
{
    bool debug = (argc != 1);
    Joystick js(JOYSTICK_DEVICE);
    std::thread t1(joystick_thread, &js, debug);

    udpLink_t link;
    udpInit(&link, FCL_FC_ADDR, FCL_FC_PORT, false);
    fcl_joystick_t j = {0};

    while (true)
    {
        try
        {
            j.button = 0;
            j.axis[0] = js.get_axis(Joystick::eRoll);
            j.axis[1] = js.get_axis(Joystick::ePitch);
            j.axis[2] = js.get_axis(Joystick::eThrottle);
            j.axis[3] = js.get_axis(Joystick::eYaw);
            j.axis[4] = js.get_axis(Joystick::eAux);
            j.button |= (js.get_button_state(0) ? 1 : 0);
            j.button |= (js.get_button_state(1) ? 2 : 0);
            j.button |= (js.get_button_state(2) ? 4 : 0);
            j.button |= (js.get_button_state(3) ? 8 : 0);
            j.button |= (js.get_button_state(4) ? 16 : 0);

            std::this_thread::sleep_for(std::chrono::milliseconds(RC_UPDATE_SLEEP_MS));
            fcl_send_data(&link, eJoystick, &j);
        }
        catch (boost::exception &e)
        {
            std::cerr << boost::diagnostic_information(e);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    //socket.close();
    t1.join();

    return 0;
}