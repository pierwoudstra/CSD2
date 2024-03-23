/*
 * todo:
 * - fix dry/wet amount not having influence
 * - change way effects react to osc
 * - maybe add another osc parameter
 */

#include <iostream>
#include <thread>

#include "Callback.h"
#include "osc_server.h"

int main() {

  auto callback = CustomCallback{};
  auto jackModule = JackModule{callback};
  localOSC osc = localOSC{callback};

  jackModule.init(1, 2);

  osc.runServer();

  bool running = true;
  while (running) {
    switch (std::cin.get()) {
    case 'q':
      running = false;
      break;
    case 'w':
      break;
    }
  }

  return 0;
}
