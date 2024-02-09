#include "Tremolo.h"

Tremolo::Tremolo(float dryWetAmt, float frequency, float modDepth)
    : Effect(dryWetAmt) {
  lfo = Sine(frequency);
  this->frequency = frequency;
  this->modDepth = modDepth;
}

Tremolo::~Tremolo() {}

void Tremolo::prepare(float sampleRate) {
  lfo.prepare(sampleRate);
}

float Tremolo::processFrame(float input) {
  // more or less same code as Ciska's
  float modSignal = lfo.genNextSample() * 0.5f + 0.5f; // use lfo as modulator
  modSignal *= modDepth; // apply mod-depth
  modSignal += 1.f - modDepth;

  return input * modSignal;
}
