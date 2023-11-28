#include "Sine.h"
#include <cmath>

#define PI 3.14159265359

// constructor & destructor

Sine::Sine(int sampleRate, float frequency, float amplitude)
    : Oscillator(sampleRate, frequency, amplitude) {
  this->sampleRate = sampleRate;
  this->frequency = frequency;
  this->amplitude = amplitude;

  phase = 0.0f;
  sample = 0.0f;
}

Sine::~Sine() {}

//

float Sine::getSample() { return sample; }

void Sine::tick() {
  // increment phase inside sine function
  phase += frequency / sampleRate;
  sample = amplitude * sin(PI * 2 * phase);
}
