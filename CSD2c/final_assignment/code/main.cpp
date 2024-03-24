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
      std::cout << "starting program" << std::endl;

    auto callback = CustomCallback{};
    std::cout << "starting Jack" << std::endl;

    auto jackModule = JackModule{callback};

    std::cout << "starting osc" << std::endl;

    localOSC osc = localOSC{callback};

    callback.innitEffects();

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
