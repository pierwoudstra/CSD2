#ifndef CALLBACK_H
#define CALLBACK_H

#include "PitchShifter.h"
#include "delay.h"
#include "jack_module.h"
#include "tremolo.h"
#include "ui.h"
#include "waveshaper.h"
#include "Chorus.h"

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  float samplerate = 44100;
  Tremolo tremolo = Tremolo(6, 1);
  Delay delay = Delay(0.7f, 2048, 2048, 0.5f);
  Waveshaper waveshaper =
      Waveshaper(1.f, Waveshaper::WaveshapeType::DIGITAL, 2.f);
  PitchShifter pitchShifter = PitchShifter(0.5f, 1.3f);
  PitchShifter pitchShifter2 = PitchShifter(0.5f, 1.3f);
  Chorus chorus = Chorus(0.2f, 1.f, 0.5f, samplerate);
  Chorus chorus2 = Chorus(0.2f, 0.7f, 0.5f, samplerate);

};

#endif // CALLBACK_H
