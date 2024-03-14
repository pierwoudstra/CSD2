#include "Tremolo.h"

Tremolo::Tremolo(float wet, float frequency, float modDepth) : Effect(wet) {
  this->frequency = frequency;
  this->modDepth = modDepth;
  lfo = Sine(frequency); // init lfo frequency
}

Tremolo::~Tremolo() {}

void Tremolo::prepare(float sampleRate) {
  lfo.prepare(sampleRate); // calls sine prepare function
}

float Tremolo::applyEffect(float input) {
  // more or less same code as Ciska's
  float modSignal = lfo.genNextSample() * 0.5f + 0.5f; // use lfo as modulator
  // apply mod-depth
  modSignal *= modDepth;
  modSignal += 1.f - modDepth;

  // return wet output
  return input * modSignal;
}
