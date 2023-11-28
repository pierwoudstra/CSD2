#include "Oscillator.h"
#include "Sine.h"
#include "writeToFile.h"
#include <iostream>

int main() {
  Sine sinus(44100, 220.0f, 0.5f);

  sinus.setFrequency(230.0f);

  sinus.setAmplitude(0.4f);

  WriteToFile fileWriter("output.csv", true);
  for(int i = 0; i < 44100; i++) {
    fileWriter.write(std::to_string(sinus.getSample()) + "\n");
    sinus.tick();
  }
}
