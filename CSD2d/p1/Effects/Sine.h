#include "Oscillator.h"
#include <cmath>

#define PI 3.14159265359

#ifndef SINE_H
#define SINE_H

class Sine : public Oscillator {
public:
  Sine(float sampleRate = 44100, float frequency = 4.f, float amplitude = 1.f)
      : Oscillator(sampleRate, frequency, amplitude) {
    this->sampleRate = sampleRate;
    this->frequency = frequency;
    this->amplitude = amplitude;

    phase = 0.0f;
    sample = 0.0f;
  }
  ~Sine() {}

  // returns current sample
  float getSample() { return sample; }
  // increments phase
  void tick() {
    // increment phase inside sine function
    phase += frequency / sampleRate;
    sample = amplitude * sin(PI * 2 * phase);
  }

private:
  float sample;
};

#endif // SINE_H
