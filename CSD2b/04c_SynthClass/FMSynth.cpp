#include "FMSynth.h"

FMSynth::FMSynth(float amplitude, float sampleRate, float midiNote, float fmRatio, float fmAmt)
    : Synth(amplitude, sampleRate) {
  frequency = midiToFrequency(midiNote);
  this->fmRatio = fmRatio;
  this->fmAmt = fmAmt;

  // amplitude envelope
  envelopes[0] = new Envelope(0.1f, 0.9f, false, sampleRate);
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

  // to make sure assigning frequency again to modulator
  oscillators[1]->setFrequency(frequency * fmRatio);

  // carrier gets modulated
  oscillators[0]->setFrequency(frequency + (oscillators[1]->getSample() * 20.f) );

  // assign value to output sample
  sample = oscillators[0]->getSample() * envelopes[0]->getValue();

  // update oscillators and envelopes
  oscillators[0]->tick();
  oscillators[1]->tick();
  envelopes[0]->tick();
  envelopes[1]->tick();
}
