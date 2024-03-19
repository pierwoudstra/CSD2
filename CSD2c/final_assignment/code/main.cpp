#include <iostream>

#include "Callback.h"

#include "Effects/Chorus.h"
#include "Effects/Delay.h"
#include "Effects/Effect.h"
#include "Effects/PitchShifter.h"
#include "Effects/Tremolo.h"
#include "Effects/Waveshaper.h"

int main() {

  auto callback = CustomCallback{};
  auto jackModule = JackModule{callback};
  // TODO:
  // EffectChain effectChain(callback);
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
