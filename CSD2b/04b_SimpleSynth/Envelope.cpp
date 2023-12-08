#include "Envelope.h"
#include <iostream>

Envelope::Envelope(int sampleRate) {
  this->sampleRate = sampleRate;
  phase = 0.f;
  value = 0.f;
}

Envelope::~Envelope(){}

float Envelope::getValue() {
  return value;
}

void Envelope::tick() {
  phase += 1.f / float(sampleRate);

  if (phase < 0.25f) {
    value = 4.f * phase;
  } else if (phase > 0.25f && phase < 1.f) {
    value = (-1 / 0.75) * phase + (1 / 0.75);
  } else if (phase > 1.f) {
    value = 0.f;
  }

  std::cout << value << std::endl;
}

void Envelope::resetPhase() {
  phase = 0.f;
}
