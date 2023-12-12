#ifndef INC_04C_SYNTHCLASS_KICKSYNTH_H
#define INC_04C_SYNTHCLASS_KICKSYNTH_H

#include "Synth.h"
#include "Sine.h"

class KickSynth : public Synth {
public:
  KickSynth(float amplitude, float sampleRate, float midiNote, float distortion);
  ~KickSynth();

  void tick();

private:
  float distortion;

};

#endif // INC_04C_SYNTHCLASS_KICKSYNTH_H
