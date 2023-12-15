#ifndef INC_04C_SYNTHCLASS_FMSYNTH_H
#define INC_04C_SYNTHCLASS_FMSYNTH_H

#include "Sine.h"
#include "Synth.h"

class FMSynth : public Synth {
public:
  FMSynth(float amplitude, float sampleRate, float midiNote, float fmRatio,
          float fmAmt);
  ~FMSynth();

  void tick();
  float getFrequency();

private:
  float fmRatio;
  float fmAmt;
};

#endif // INC_04C_SYNTHCLASS_FMSYNTH_H
