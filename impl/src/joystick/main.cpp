// Written by Stefan Schmidt 2019

// use jstest-gtk
// jscal -t /dev/input/js0
// sudo jscal-store /dev/input/js0
// jscal-restore
// /var/lib/joystick/joystick.state

#include "Joystick.h"
#include "fcl_base.h"
#include "fcl_cfg.h"
#include "fcl_types.h"
#include "udplink.h"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <unistd.h>

#define JOYSTICK_DEVICE "/dev/input/js0"
#define RC_UPDATE_SLEEP_MS 20

void joystick_thread(Joystick *js, bool debug)
{

  printf("axis: %i, btn: %i\n", js->get_axis_count(), js->get_button_count());

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

  uint32_t l = 0;
  bool debug = (argc != 1);
  Joystick js(JOYSTICK_DEVICE);
  std::thread t1(joystick_thread, &js, false);

  udpLink_t link;
  udp_init(&link, FCL_FC_ADDR, FCL_FC_PORT, false);
  fcl_joystick_t j = {0};

  while (true)
  {
    j.button = 0;
    for (uint32_t i = 0; i < MAX_RC_CHANNELS; i++)
    {
      j.val[i] = js.get_axis_raw(i);
    }
    /*
    j.val[0] = js.get_axis_raw(Joystick::eRoll);
    j.val[1] = js.get_axis_raw(Joystick::ePitch);
    j.val[2] = js.get_axis_raw(Joystick::eThrottle);
    j.val[3] = js.get_axis_raw(Joystick::eYaw);
    j.val[4] = js.get_axis_raw(Joystick::eAux);
    j.axis[0] = js.get_axis(Joystick::eRoll);
    j.axis[1] = js.get_axis(Joystick::ePitch);
    j.axis[2] = js.get_axis(Joystick::eThrottle);
    j.axis[3] = js.get_axis(Joystick::eYaw);
    j.axis[4] = js.get_axis(Joystick::eAux);
    */
    j.button |= (js.get_button_state(0) ? 1 : 0);
    j.button |= (js.get_button_state(1) ? 2 : 0);
    j.button |= (js.get_button_state(2) ? 4 : 0);
    j.button |= (js.get_button_state(3) ? 8 : 0);
    j.button |= (js.get_button_state(4) ? 16 : 0);
    if (debug)
    {
      printf("%u: %f %f %f %f %f %u\n", l++, j.val[0], j.val[1], j.val[2], j.val[3], j.val[4], j.button );
    }

    fcl_send_data(&link, eJoystick, &j);
    usleep(RC_UPDATE_SLEEP_MS * 1000u);
  }

  t1.join();
  return 0;
}