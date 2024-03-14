#ifndef CALLBACK_H
#define CALLBACK_H

#include "delay.h"
#include "jack_module.h"
#include "tremolo.h"
#include "waveshaper.h"

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  float samplerate = 44100;
  Tremolo tremolo = Tremolo(6, 1);
  Delay delay;
  Waveshaper waveshaper;
};

#endif // CALLBACK_H
