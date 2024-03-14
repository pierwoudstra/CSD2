#include "Effect.h"
#include "Tremolo.h"
#include "audioToFile.h"
#include <math.h>

int main() {
  Tremolo tremolo = Tremolo(0.8f, 3.f, 0.6f);
  // Delay delay = Delay(0.5f, 0.2f);

  // init write to file
  WriteToFile fileWriter("output.csv", true);

  // attempt at amplitude modulation
  for (int i = 0; i < (44100 * 4); i++) {
    fileWriter.write(std::to_string(tremolo.processFrame(sin(i * 100.f / 44100.f))) + "\n");
  }

}
