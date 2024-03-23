#include "Effect.h"
#include <iostream>

Effect::Effect(float dryWet) {
  setDryWet(dryWet);
  setBypass(false);
}

Effect::~Effect() {}

// process frame
void Effect::processFrame(const float &input, float &output) {
  // using bypass to determine signal
  if (bypass) {
    output = input;
  } else {
    applyEffect(input, output);
//    std::cout << "from fx baseclass: " << dryWet << std::endl;
    output = input * float(wetDry) + output * float(dryWet);
  }
  // cache output samples
  m_sample = output;
}

// returns the last outputted sample
float Effect::getSample() { return m_sample; }

void Effect::setDryWet(float dryWet) {
  if (dryWet < 0.f || dryWet > 1.f) {
    throw "Effect::setDryWet - dryWet value is not in range [0, 1]";
  }
  this->dryWet = dryWet;
  // cache 1.0 - dryWet used to calculate mix of dry wet signal
  wetDry = float(1.0f - dryWet);
}

void Effect::setBypass(bool bypass) { this->bypass = bypass; }
