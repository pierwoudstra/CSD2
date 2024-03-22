#ifndef CALLBACK_H
#define CALLBACK_H

#include "jack_module.h"
#include "Melody.h"
#include "sine.h"
#include "oscillator.h"

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;
  double mtof(float mPitch);
  void updatePitch(Melody& melody, Oscillator& myFastSine);

private:
  float samplerate = 44100;
  int frameIndex = 0;
  double noteDelayFactor = 0.5;
  Melody melody;
  Sine sine = Sine(400, samplerate);
  
};

#endif // CALLBACK_H
