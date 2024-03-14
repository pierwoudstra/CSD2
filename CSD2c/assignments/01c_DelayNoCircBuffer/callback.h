#ifndef CALLBACK_H
#define CALLBACK_H

#include "jack_module.h"
#include "Tremolo.h"
#include "Delay.h"


class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  float samplerate = 44100;
  Tremolo tremolo = Tremolo(0.5f, 3.f, 0.7f);
  Delay delay = Delay(0.f, 44100, 44100, 0.5f);
};

#endif //CALLBACK_H
