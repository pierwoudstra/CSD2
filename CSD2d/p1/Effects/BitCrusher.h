#pragma once
#include "Effect.h"
#include <cmath>
#include <iostream>

class BitCrusher : public Effect {
public:
  BitCrusher(float bitDepth = 16.f, float dryWet = 1.f)
      : Effect(dryWet), bitDepth(bitDepth) {
    setQuantizedBitDepth(bitDepth);
  }

  ~BitCrusher() { std::cout << "BitCrusher Destructor" << std::endl; }

  void setQuantizedBitDepth(float bitDepth) {
    quantizationLevel = 2.0 / (pow(2.0, bitDepth) - 1.0);
  }

private:
  void applyEffect(const float &input, float &output) override {
    output = quantizationLevel * float(int(input / quantizationLevel));
  }

  float bitDepth;
  float quantizationLevel;
};
