#ifndef INC_04C_SYNTHCLASS_DETUNEDSAW_H
#define INC_04C_SYNTHCLASS_DETUNEDSAW_H

#include "Saw.h"
#include "Synth.h"

class DetunedSaw : public Synth {
public:
  DetunedSaw(float amplitude, float sampleRate, float midiNote,
             float detuneAmt);
  ~DetunedSaw();

  void tick();

private:
  float detuneAmt;
};

#endif // INC_04C_SYNTHCLASS_DETUNEDSAW_H
