#include "Tremolo.h"

Tremolo::Tremolo(float dryWetAmt, float frequency, float modDepth)
    : Effect(dryWetAmt) {
  this->frequency = frequency;
  this->modDepth = modDepth;

}

Tremolo::~Tremolo() {}

void Tremolo::prepare(float sampleRate) {
  lfo.prepare(sampleRate);
}

float Tremolo::processFrame(float input) {
  // process frame
  return 0;
}
