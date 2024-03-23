// control effects based on incoming osc values

#include <iostream>

#include "Effects/BitCrusher.h"
#include "Effects/Chorus.h"
#include "Effects/Delay.h"
#include "Effects/Effect.h"
#include "Effects/PitchShifter.h"
#include "Effects/Tremolo.h"
#include "Effects/Waveshaper.h"

#ifndef FINAL_ASSIGNMENT_EFFECTCONTROLLER_H
#define FINAL_ASSIGNMENT_EFFECTCONTROLLER_H

class EffectController {
public:
  EffectController();
  ~EffectController();

  void prepare(float samplerate);
  void processFrame(const float &input, float &output);

  void setCompassValue(int compassValue);
  void setEffectValue();

private:
  int compassValue = 0; // value from 0 - 360

  float samplerate = 44100;
  Tremolo tremolo = Tremolo(6, 1);
  Delay delay = Delay(0.7f, 2048, 2048, 0.5f);
  Waveshaper waveshaper =
      Waveshaper(1.f, Waveshaper::WaveshapeType::DIGITAL, 2.f);
  PitchShifter pitchShifter = PitchShifter(0.5f, 1.3f);
  PitchShifter pitchShifter2 = PitchShifter(0.5f, 1.3f);
  Chorus chorus = Chorus(0.2f, 0.9f, 0.5f, samplerate);
  Chorus chorus2 = Chorus(0.2f, 0.7f, 0.5f, samplerate);
  BitCrusher bitCrusher = BitCrusher(4.0, 1.0);
};

#endif // FINAL_ASSIGNMENT_EFFECTCONTROLLER_H
