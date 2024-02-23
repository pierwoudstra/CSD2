#include "delay.h"
#include "effect.h"
#include "oscillator.h"

#ifndef INC_03_PRESENTATION_CHORUS_H
#define INC_03_PRESENTATION_CHORUS_H

class Chorus : public Effect {
public:
  Chorus(float dryWet = 1.f, float modFreq = 5.f, float modDepth = 1.f, float samplerate = 44100);
  ~Chorus();

  void prepare(float samplerate) override;
  void applyEffect(const float &input, float &output) override;

  // TODO add setters

private:
  Oscillator *lfo;
  Delay *delay;

  float modFreq;
  float modDepth;
  float samplerate;
  float modSignal = 0;
};

#endif // INC_03_PRESENTATION_CHORUS_H
