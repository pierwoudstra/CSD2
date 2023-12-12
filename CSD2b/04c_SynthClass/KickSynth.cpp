#include "KickSynth.h"

KickSynth::KickSynth(float amplitude, float sampleRate, float midiNote,
                     float drive)
    : Synth(amplitude, sampleRate) {
  frequency = midiToFrequency(midiNote);
  this->drive = drive;

  // amplitude envelope
  envelopes[0] = new Envelope(0.05f, 0.6f, false, sampleRate);
  // frequency envelope
  envelopes[1] = new Envelope(0.f, 0.1f, false, sampleRate);

  oscillators[0] = new Sine(frequency, amplitude, sampleRate);
  oscillators[1] = NULL;
  oscillators[2] = NULL;
}

KickSynth::~KickSynth() {}

void KickSynth::tick() {
  // update phase
  phase += increment;
  if (phase > 1.0f) {
    phase -= 1.0f;
  }

  oscillators[0]->setFrequency(frequency + (envelopes[1]->getValue() * 700.f));

  // assign value to output sample
  sample =
      (tanh(oscillators[0]->getSample() * drive * envelopes[0]->getValue()) *
       amplitude);

  // update oscillator and envelope
  oscillators[0]->tick();
  envelopes[0]->tick();
  envelopes[1]->tick();
}
