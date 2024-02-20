#include "effect.h"

#define bufSize 1000
#define overlap 100

#ifndef INC_03_PRESENTATION_PITCHSHIFTER_H
#define INC_03_PRESENTATION_PITCHSHIFTER_H

class PitchShifter : public Effect {
public:
  PitchShifter(float dryWet = 1.f, float shift = 2.f);
  ~PitchShifter();

  void applyEffect(const float &input, float &output) override;

private:
  float* buffer;
  int writeHead;
  float readHead;
  float shift;
  float crossFade;


};

#endif // INC_03_PRESENTATION_PITCHSHIFTER_H
