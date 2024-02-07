#include "EffectClass.h"

EffectClass::EffectClass(float dryWetAmt = 0.5) {
  this->dryWetAmt = dryWetAmt;
  output = ((1 - dryWetAmt) * input) + (dryWetAmt * wetOutput);
}

EffectClass::~EffectClass() {}

void EffectClass::setDryWet(float dryWetAmt) {
  this->dryWetAmt = dryWetAmt;
  output = ((1 - dryWetAmt) * input) + (dryWetAmt * wetOutput);
}
