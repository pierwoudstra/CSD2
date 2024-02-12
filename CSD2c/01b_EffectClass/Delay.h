#include "Effect.h"
#include "CircBuffer.h"

#ifndef INC_01B_EFFECTCLASS_DELAY_H
#define INC_01B_EFFECTCLASS_DELAY_H

class Delay : public Effect {
public:
  Delay(float dryWetAmt, float delayTime);
  ~Delay();

  void prepare(float sampleRate);
  float processFrame(float input);

private:
  float delayTime; // delay time in seconds
  CircBuffer buffer;
};

#endif // INC_01B_EFFECTCLASS_DELAY_H
