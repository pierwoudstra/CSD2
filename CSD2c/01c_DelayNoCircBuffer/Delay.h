#include "Effect.h"

#ifndef INC_01C_DELAYNOCIRCBUFFER_DELAY_H
#define INC_01C_DELAYNOCIRCBUFFER_DELAY_H

class Delay : public Effect {
public:
  Delay(float feedback = 0.f, int numDelaySamples = 2048,
        int maxDelaySize = 2048, float wet = 0.5f);
  ~Delay();

  // overridden virtual methods
  float applyEffect(float input) override;

  // setters
  void setNumDelaySamples(int numDelaySamples);
  void setFeedback(float feedback);

private:
  inline void wrapHead(int& head) {
    if (head > maxDelaySize) {
      head -= maxDelaySize;
    }
  }

  float feedback;

  float* buffer;
  int numDelaySamples;
  int maxDelaySize;
  int readHead;
  int writeHead;
};

#endif // INC_01C_DELAYNOCIRCBUFFER_DELAY_H
