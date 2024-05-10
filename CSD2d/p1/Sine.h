#include "Oscillator.h"

#ifndef SINE_H
#define SINE_H

class Sine : public Oscillator {
public:
  Sine(int sampleRate, float frequency, float amplitude);
  ~Sine();

  // returns current sample
  float getSample();
  // increments phase
  void tick();

private:
  float sample;
};

#endif // SINE_H
