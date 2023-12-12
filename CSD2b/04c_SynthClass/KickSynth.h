#ifndef INC_04C_SYNTHCLASS_KICKSYNTH_H
#define INC_04C_SYNTHCLASS_KICKSYNTH_H

#include "Sine.h"
#include "Synth.h"

class KickSynth : public Synth {
public:
  KickSynth(float amplitude, float sampleRate, float midiNote, float drive);
  ~KickSynth();

  void tick();

private:
  float drive;
};

#endif // INC_04C_SYNTHCLASS_KICKSYNTH_H
