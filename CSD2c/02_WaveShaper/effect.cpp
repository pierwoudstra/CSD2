#include "effect.h"

Effect::Effect(float dryWet) {
  setDryWet(dryWet);
  setBypass(false);
}

Effect::~Effect() {}

// process frame
void Effect::processFrame(const float &input, float &output) {
  if (bypass) {
    output = input;
  } else {
    applyEffect(input, output);
    output = input * wetDry + output * dryWet;
  }
  // cache output samples
  m_sample = output;
}

// returns the last outputted sample
float Effect::getSample() { return m_sample; }

void Effect::setDryWet(float dryWet) {
  if (dryWet < 0 || dryWet > 1) {
    throw "Effect::setDryWet - dryWet value is not in range [0, 1]";
  }
  this->dryWet = dryWet;
  // cache 1.0 - dryWet used to calculate mix of dry wet signal
  wetDry = 1.0f - dryWet;
}

void Effect::setBypass(bool bypass) {
  this->bypass = bypass;
}
