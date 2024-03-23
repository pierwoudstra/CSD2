#ifndef CALLBACK_H
#define CALLBACK_H

#include "EffectController.h"
#include "Melody.h"
#include "jack_module.h"
#include "oscillator.h"
#include "sine.h"

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;
  double mtof(float mPitch);
  void updatePitch(Melody &melody, Oscillator &myFastSine);
  void setOsc(float oscValue);

private:
  float oscValue = 0.f;
  EffectController effects;
  float samplerate = 44100;
  int frameIndex = 0;
  double noteDelayFactor = 0.5;
  Melody melody;
  Sine sine = Sine(400, samplerate);
};

#endif // CALLBACK_H
