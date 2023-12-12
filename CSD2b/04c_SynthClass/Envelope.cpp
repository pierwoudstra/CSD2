#include "Envelope.h"

Envelope::Envelope(float attack, float decay, bool loop, int sampleRate) {
  this->attack = attack;
  this->decay = decay;
  this->loop = loop;
  this->sampleRate = sampleRate;
  phase = 0.f;
  value = 0.f;
}

Envelope::~Envelope() {}

float Envelope::getValue() { return value; }

void Envelope::tick() {
  phase += 1.f / float(sampleRate);

  if (phase < attack) {

    value = (1.f / attack) * phase;

  } else if (phase > attack && phase < decay) {

    value = (phase - attack) / (attack - decay) + 1.f;

  } else if (phase > 1.f) {

    if (loop) {
      resetPhase();
    } else {
      value = 0.f;
    }
  }
}

void Envelope::resetPhase() { phase = 0.f; }
