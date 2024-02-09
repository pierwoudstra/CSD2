#include "Effect.h"
#include "sine.h"
#include <iostream>

#ifndef INC_01B_EFFECTCLASS_TREMOLO_H
#define INC_01B_EFFECTCLASS_TREMOLO_H

class Tremolo : public Effect {
public:
  Tremolo(float dryWetAmt, float frequency, float modDepth);
  ~Tremolo();

  void prepare(float sampleRate); // initializes lfo sample-rate
  float processFrame(float input);

  void setModDepth();

private:
  float frequency;
  float modDepth; // mod depth from 0 to 1
  Sine lfo;
};

#endif // INC_01B_EFFECTCLASS_TREMOLO_H
