#include <iostream>

#include "Callback.h"

int main() {
  // todo
  auto callback = CustomCallback{};
  auto jackModule = JackModule{callback};

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
