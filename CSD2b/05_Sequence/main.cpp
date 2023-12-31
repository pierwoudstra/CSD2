#include "Callback.h"

/*
 * sounding sequence using Marc & Ciska's
 * code but with own classes & synth designs
 */

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

int main() {

  // most of the workings are in the Callback.h file

  auto callback = CustomCallback{};
  auto jackModule = JackModule{callback};

  jackModule.init(0, 1);

  bool running = true;
  while (running) {
    switch (std::cin.get()) {
    case 'q':
      running = false;
    }
  }

  // end the program
  return 0;
}
