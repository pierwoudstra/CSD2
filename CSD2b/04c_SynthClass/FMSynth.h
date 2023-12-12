#ifndef INC_04C_SYNTHCLASS_FMSYNTH_H
#define INC_04C_SYNTHCLASS_FMSYNTH_H

#include "Synth.h"
#include "Sine.h"

class FMSynth : public Synth {
public:
  FMSynth(float amplitude, float sampleRate, float midiNote, float fmRatio, float fmAmt);
  ~FMSynth();

  void tick();

private:
  float fmRatio;
  float fmAmt;
};

#endif // INC_04C_SYNTHCLASS_FMSYNTH_H
