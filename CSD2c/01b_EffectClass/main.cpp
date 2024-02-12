#include "Effect.h"
#include "Tremolo.h"
#include "audioToFile.h"
#include "Delay.h"

int main() {
  Tremolo tremolo = Tremolo(0.8f, 3.f, 0.6f);

  // init write to file
  WriteToFile fileWriter("output.csv", true);

  // attempt at amplitude modulation
  for (int i = 0; i < 44100; i++) {
    fileWriter.write(std::to_string(tremolo.processFrame(1)) + "\n");
  }

}
