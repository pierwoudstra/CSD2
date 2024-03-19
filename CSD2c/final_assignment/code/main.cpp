#include <iostream>

#include "Callback.h"
#include "EffectController.h"

int main() {

  auto callback = CustomCallback{};
  auto jackModule = JackModule{callback};
  // TODO:
  // EffectController effectController(callback);
  // UIController uiController(effectChain);

  jackModule.init(1, 2);

  bool running = true;
  while (running) {
    switch (std::cin.get()) {
    case 'q':
      running = false;
    }
  }

  return 0;
}
