#include "Effect.h"
#include "Sine.h"
#include <cmath>

#ifndef MYPROJECT_TREMOLO_H
#define MYPROJECT_TREMOLO_H

class Tremolo : public Effect {
public:
  Tremolo(float frequency = 5.f, float modDepth = 1.f,
          float sampleRate = 44100) {
    sine = new Sine(sampleRate, frequency, 1.f);
  }

  ~Tremolo() {}

  void applyEffect(const float &input, float &output) override {
    float modSignal = sine->getSample() * 0.5f + 0.5f;

    modSignal *= modDepth;
    modSignal += 1.f - modDepth;

    output = input * modSignal;
    sine->tick();
  }

  // setters
  void setSampleRate(float sampleRate) { this->sampleRate = sampleRate; }

  void setFrequency(float frequency) {
    this->frequency = frequency;
    sine->setFrequency(frequency);
  }

  void setModDepth(float modDepth) { this->modDepth = modDepth; }

private:
  float frequency;
  float modDepth;
  float sampleRate;

  Sine *sine;
};

#endif // MYPROJECT_TREMOLO_H
