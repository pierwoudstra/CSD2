/*
 * todo:
 * - find way to use OSC value in callback
 * - fix effect controller class (rn no output)
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

  std::thread oscServerThread([&osc]() { osc.runServer(); });
  std::thread getOscThread([&osc]() { osc.getOscValue(); });

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

  oscServerThread.join();
  getOscThread.join();

  return 0;
}
