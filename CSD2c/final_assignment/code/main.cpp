/*
 * OSC EFFECT CONTROLLER
 * by Roman-James & Pier
 * using Ciska's delay & effect baseclass
 * using Marc's wrapper for liblo
 */

#include <iostream>
#include <thread>

#include "Callback.h"
#include "osc_server.h"

int main() {
  std::cout << "starting program" << std::endl;
  auto callback = CustomCallback{};
  auto jackModule = JackModule{callback};

  // call effect constructors
  callback.initEffects();

  localOSC osc = localOSC{callback};

  std::cout << "starting Jack" << std::endl;
  jackModule.init(1, 2);

  std::cout << "starting OSC server" << std::endl;
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
