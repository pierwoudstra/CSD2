#include "Effect.h"
#include "CircBuffer.h"

#ifndef INC_01B_EFFECTCLASS_DELAY_H
#define INC_01B_EFFECTCLASS_DELAY_H

class Delay : public Effect {
public:
  Delay(float wet, float delayTime);
  ~Delay();

  // overridden virtual methods
  void prepare(float sampleRate) override;
  float applyEffect(float input) override;

private:
  float delayTime; // delay time in seconds
  CircBuffer buffer;
};

#endif // INC_01B_EFFECTCLASS_DELAY_H
