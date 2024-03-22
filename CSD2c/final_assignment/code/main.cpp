#include <iostream>
#include <thread>

#include "Callback.h"
#include "osc_server.h"
int main() {

  auto callback = CustomCallback{};
  auto jackModule = JackModule{callback};
  localOSC osc;

  jackModule.init(1, 2);

  std::thread oscServerThread([&osc]() { osc.runServer(); });
  std::thread getOscThread([&osc]() { osc.getOscValue(); });

  int oscValue;

  // if osc-input changes, change osc-value variable
  while (true) {
      if (oscValue != osc.getOscValue()) {
        oscValue = osc.getOscValue();
        std::cout << "printing from main: " << oscValue << std::endl;
      }
      usleep(1000);
  }

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
