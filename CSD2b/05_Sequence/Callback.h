#include "DetunedSaw.h"
#include "FMSynth.h"
#include "KickSynth.h"
#include "Sine.h"
#include "jack_module.h"
#include "melody.h"

#include <iostream>

#ifndef CALLBACK_H
#define CALLBACK_H

class CustomCallback : public AudioCallback {
public:
  void updatePitch(Melody &melody, DetunedSaw &saw);
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  float sampleRate = 44100;
  KickSynth kick = KickSynth(0.9f, sampleRate, 33.f, 70.f);
  DetunedSaw saw = DetunedSaw(0.9f, sampleRate, 50.f, 8.f);
  FMSynth fm = FMSynth(1.f, 44100, 48.0f, 7.7f, 20.f);

  Melody melody;
  int frameIndex = 0;
  // counts eighth notes
  int counter = 0;

  // delay factor used instead of bpm
  float noteDelayFactor = 0.19;

  std::string synthChoice[2] = {"fm-synth", "dance-lead"};
  std::string songChoice[3] = {"nokia", "tetris", "titanic"};
};

#endif // CALLBACK_H
