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
  double mtof(float mPitch);
  void updatePitch(Melody &melody, Oscillator &myFastSine);
  void setOsc(float oscValue);

private:
  float oscValue = 0.f;
  float samplerate = 44100;
  int frameIndex = 0;
  double noteDelayFactor = 0.5;
  Melody melody;
  float dryWet = 1.f;

  // effects:
  Sine sine = Sine(400, samplerate);
  //  Delay delay = Delay(0.7f, 2048, 2048, 0.f);
  Waveshaper* waveshaper;
  Delay* delay;
  //  PitchShifter pitchShifter2 = PitchShifter(0.f, 1.3f);
  //  Chorus chorus = Chorus(0.f, 0.9f, 0.5f, samplerate);
  //  Chorus chorus2 = Chorus(0.f, 0.7f, 0.5f, samplerate);
  //  BitCrusher bitCrusher = BitCrusher(4.0, 1.f);
};

#endif // CALLBACK_H
