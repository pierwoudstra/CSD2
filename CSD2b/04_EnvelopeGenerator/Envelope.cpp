#include "Envelope.h"

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

  if (phase < 0.33f) {
    value = 2.f * phase;
  } else if (phase > 0.33f) {
    value = 1.f - phase;
  }
}
