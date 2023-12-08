#include "Envelope.h"
#include "writeToFile.h"

int main() {
  const int SAMPLE_RATE = 44100;

  Envelope env = Envelope(0.01f, 0.2f, true, SAMPLE_RATE);

  // init write to file
  WriteToFile fileWriter("output.csv", true);

  // attempt at amplitude modulation
  for (int i = 0; i < SAMPLE_RATE * 2; i++) {
    fileWriter.write(std::to_string(env.getValue()) + "\n");
    env.tick();
  }

}
