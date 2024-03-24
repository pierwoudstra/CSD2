#include "Effect.h"

// idea for most of this code from YT channel:
// YetAnotherElectronicsChannel
// title of video:
// [#7] Pitch Shifting - Audio DSP On STM32 (24 Bit / 96 kHz)

#define bufSize 1000
#define overlap 100

#ifndef INC_03_PRESENTATION_PITCHSHIFTER_H
#define INC_03_PRESENTATION_PITCHSHIFTER_H

class PitchShifter : public Effect {
public:
  PitchShifter(float dryWet = 1.f, float shift = 2.f);
  ~PitchShifter();

  void applyEffect(const float &input, float &output) override;
  void setPitch(float shift);

private:
  float *buffer;
  int writeHead;
  float readHead;
  float shift;
  float crossFade;
};

#endif // INC_03_PRESENTATION_PITCHSHIFTER_H
