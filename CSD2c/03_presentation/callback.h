#ifndef CALLBACK_H
#define CALLBACK_H

#include "delay.h"
#include "jack_module.h"
#include "tremolo.h"
#include "waveshaper.h"
#include "ui.h"

class CustomCallback : public AudioCallback {
public:

  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  float samplerate = 44100;
  Tremolo tremolo = Tremolo(6, 1);
  Delay delay = Delay(0.7f, 2048, 2048, 0.5f);
  Waveshaper waveshaper = Waveshaper(1.f, WaveshapeType::HARD, 1.5f);
  UI ui;

  int tremoloOn;
  int waveshaperOn;
  int delayOn;
};

#endif // CALLBACK_H
