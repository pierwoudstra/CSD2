#include <iostream>
#include <thread>

#include "Callback.h"
#include "EffectController.h"
#include "osc_server.h"
int main() {

  auto callback = CustomCallback{};
  auto jackModule = JackModule{callback};
  localOSC osc;

  // TODO:
  // EffectController effectController(callback);
  // UIController uiController(effectChain);

  jackModule.init(1, 2);

  

  osc.runServer();

  bool running = true;
  while (running) {
    switch (std::cin.get()) {
    case 'q':
      running = false;
      break;
    case 'w':
      std::cout << "printing from main: " << osc.getOscValue() << std::endl;
      break;
    }
  }

  return 0;
}
