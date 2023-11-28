#include "Sine.h"
#include "writeToFile.h"
#include <iostream>

int main() {
  const int SAMPLE_RATE = 44100;

  Sine sine(SAMPLE_RATE, 220.0f, 0.5f);
  Sine modulator(SAMPLE_RATE, 7.0f, 0.7f);

  // changing the frequency so sine is visible
  sine.setFrequency(1.0f);
  sine.setAmplitude(0.9f);

  // init write to file
  WriteToFile fileWriter("output.csv", true);

  // attempt at amplitude modulation
  for (int i = 0; i < SAMPLE_RATE; i++) {
    sine.setAmplitude(modulator.getSample());
    fileWriter.write(std::to_string(sine.getSample()) + "\n");
    modulator.tick();
    sine.tick();
  }
}
