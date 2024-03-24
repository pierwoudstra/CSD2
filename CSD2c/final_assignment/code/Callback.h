#ifndef CALLBACK_H
#define CALLBACK_H

#include "Effects/BitCrusher.h"
#include "Effects/Chorus.h"
#include "Effects/Delay.h"
#include "Effects/Effect.h"
#include "Effects/PitchShifter.h"
#include "Effects/Tremolo.h"
#include "Effects/Waveshaper.h"
#include "Melody.h"
#include "jack_module.h"
#include "oscillator.h"
#include "sine.h"

class CustomCallback : public AudioCallback {
public:
  ~CustomCallback();
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;
  void initEffects();
  void updatePitch(Melody &melody, Oscillator &myFastSine);
  void setOsc(float compass, float gravityX, float gravityY);

private:
  float oscValue = 0.f;
  float oscValue2 = 0.f;
  float samplerate = 44100;
  int frameIndex = 0;
  double noteDelayFactor = 0.5;
  float dryWet;
  double QuantizedBitDepth;
  float feedback;
  float pitch;
  Melody melody;
  Sine sine = Sine(400, samplerate);

  // effects:
    PitchShifter* pitchShifter;
    BitCrusher* bitCrusher;
    Waveshaper* waveshaper;
    Delay* delay;
};

#endif // CALLBACK_H
