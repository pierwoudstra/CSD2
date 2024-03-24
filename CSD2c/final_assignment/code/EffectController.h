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

  void setDryWet(float compassValue);
  void setEffectValue(float dryWet);

  float dryWet = 0.f;

private:
  float samplerate = 44100;
//  Delay delay = Delay(0.7f, 2048, 2048, 0.f);
//  Waveshaper waveshaper =
//      Waveshaper(0.f, Waveshaper::WaveshapeType::DIGITAL, 2.f);
//  PitchShifter pitchShifter = PitchShifter(0.f, 1.3f);
//  PitchShifter pitchShifter2 = PitchShifter(0.f, 1.3f);
//  Chorus chorus = Chorus(0.f, 0.9f, 0.5f, samplerate);
//  Chorus chorus2 = Chorus(0.f, 0.7f, 0.5f, samplerate);
//  BitCrusher bitCrusher = BitCrusher(4.0, 0.f);
};

#endif // FINAL_ASSIGNMENT_EFFECTCONTROLLER_H
