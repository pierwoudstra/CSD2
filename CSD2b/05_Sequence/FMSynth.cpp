#include "FMSynth.h"
#include <iostream>

FMSynth::FMSynth(float amplitude, float sampleRate, float midiNote,
                 float fmRatio, float fmAmt)
    : Synth(amplitude, sampleRate) {
  frequency = midiToFrequency(midiNote);
  this->fmRatio = fmRatio;
  this->fmAmt = fmAmt;

  // amplitude envelope
  envelopes[0] = new Envelope(0.3f, 2.f, false, sampleRate);
  // fm-amount envelope
  envelopes[1] = new Envelope(0.01f, 0.6f, false, sampleRate);

  // carrier oscillator
  oscillators[0] = new Sine(frequency, amplitude, sampleRate);
  // modulator oscillator
  oscillators[1] = new Sine(frequency * fmRatio, fmAmt, sampleRate);
  oscillators[2] = NULL;
}

FMSynth::~FMSynth() {}

void FMSynth::tick() {
  // update phase
  phase += increment;
  if (phase > 1.0f) {
    phase -= 1.0f;
  }

  oscillators[1]->setFrequency(frequency * fmRatio);
  oscillators[1]->setAmplitude(fmAmt);

  // modulate the carrier
  oscillators[0]->setFrequency(frequency +
                               oscillators[1]->getSample() * frequency);

  // assign value to output sample
  sample = oscillators[0]->getSample();

  // update oscillators and envelopes
  oscillators[0]->tick();
  oscillators[1]->tick();
  envelopes[0]->tick();
  envelopes[1]->tick();
}

float FMSynth::getFrequency() { return frequency; }
