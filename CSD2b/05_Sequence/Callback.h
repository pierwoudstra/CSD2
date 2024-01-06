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

  void updatePitch(Melody& melody, DetunedSaw& saw);

  void prepare(int rate) override;

  void process(AudioBuffer buffer) override;

private:
  float sampleRate = 44100;
  KickSynth kick = KickSynth(0.9f, sampleRate, 20.f, 20.f);
  DetunedSaw saw = DetunedSaw(0.9f, sampleRate, 50.f, 8.f);
  FMSynth fm = FMSynth(1.f, 44100, 48.0f, 7.7f, 20.f);

  Melody melody;
  int frameIndex = 0;

  /*
     * instead of using bpm and specifying note lengths we'll make every note
     * equal length and specify the delay between notes in terms of the
     * samplerate
     *
     * A note of say 500 msec or 0.5 sec, takes 0.5 * samplerate samples to be
     * played
   */

  float noteDelayFactor = 0.1;
};

#endif // CALLBACK_H
