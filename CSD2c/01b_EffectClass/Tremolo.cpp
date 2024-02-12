#include "Tremolo.h"

Tremolo::Tremolo(float dryWetAmt, float frequency, float modDepth)
    : Effect(dryWetAmt) {
  this->frequency = frequency;
  this->modDepth = modDepth;
  lfo = Sine(frequency);
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

  wetOutput = input * modSignal;
  // make sure return value uses the dry/wet amount
  return ((1 - dryWetAmt) * input) + (dryWetAmt * wetOutput);
}
