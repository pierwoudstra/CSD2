#include "Effect.h"

Effect::Effect(float dryWetAmt) {
  this->dryWetAmt = dryWetAmt;
  output = ((1 - dryWetAmt) * input) + (dryWetAmt * wetOutput);
}

Effect::~Effect() {}

void Effect::setDryWet(float dryWetAmt) {
  this->dryWetAmt = dryWetAmt;
  output = ((1 - dryWetAmt) * input) + (dryWetAmt * wetOutput);
}
