#include "Effect.h"
#include <iostream>

Effect::Effect(float wet) { setDryWet(wet); }

Effect::~Effect() {}

void Effect::setDryWet(float wet) {
  if (wet >= 0.f && wet <= 1.f) {
    this->wet = wet;
    dry = 1.f - wet;
    std::cout << "wet: " << wet << std::endl;
    std::cout << "dry: " << dry << std::endl;
  } else {
    std::cout << "select dry/ wet value between 0 & 1" << std::endl;
  }
}

float Effect::processFrame(float input) {
  // apply effect
  output = applyEffect(input);
  // return using dry/wet
  return (dry * input) + (wet * output);
}
