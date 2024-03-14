#include "Effect.h"
#include "sine.h"
#include <iostream>

#ifndef INC_01B_EFFECTCLASS_TREMOLO_H
#define INC_01B_EFFECTCLASS_TREMOLO_H

class Tremolo : public Effect {
public:
  Tremolo(float wet, float frequency, float modDepth);
  ~Tremolo();

  // overridden virtual methods
  void prepare(float sampleRate) override; // initializes lfo sample-rate
  void setModDepth();

private:
  float applyEffect(float input) override; // the effect

  float frequency;
  float modDepth; // mod depth from 0 to 1
  Sine lfo;
};

#endif // INC_01B_EFFECTCLASS_TREMOLO_H
