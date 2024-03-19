#include "Delay.h"
#include "Effect.h"
#include "oscillator.h"

#ifndef INC_03_PRESENTATION_CHORUS_H
#define INC_03_PRESENTATION_CHORUS_H

class Chorus : public Effect {
public:
  Chorus(float dryWet = 0.5f, float modFreq = 0.5f, float modDepth = 0.5f, float samplerate = 44100);
  ~Chorus();

  void prepare(float samplerate) override;
  void applyEffect(const float &input, float &output) override;

  void setModFrequency(float modFreq);
  void setModDepth(float modDepth);
private:
  Oscillator *lfo;
  Delay *delay;

  float modFreq;
  float modDepth;
  float samplerate;
};

#endif // INC_03_PRESENTATION_CHORUS_H
