#include "DetunedSaw.h"

DetunedSaw::DetunedSaw(float amplitude, float sampleRate, float midiNote,
                       float detuneAmt)
    : Synth(amplitude, sampleRate) {
  frequency = midiToFrequency(midiNote);
  this->detuneAmt = detuneAmt;

  // amplitude envelope
  envelopes[0] = new Envelope(0.2, 0.8, false, sampleRate);
  envelopes[1] = NULL;

  oscillators[0] = new Saw(frequency, amplitude, sampleRate);
  oscillators[1] = new Saw(frequency + midiToFrequency(detuneAmt), amplitude, sampleRate);
  oscillators[2] = new Saw(frequency - midiToFrequency(detuneAmt), amplitude, sampleRate);
}

DetunedSaw::~DetunedSaw() {}

void DetunedSaw::tick() {
  // update phase
  phase += increment;
  if (phase > 1.0f) {
    phase -= 1.0f;
  }

  float oscillatorSum = oscillators[0]->getSample() +
                        oscillators[1]->getSample() +
                        oscillators[2]->getSample();

  // assign value to output sample
  sample = (oscillatorSum / 3.f) * amplitude; // * envelopes[0]->getValue();

  // update oscillators and envelope
  for (int i = 0; i < 3; i++) {
    oscillators[i]->tick();
  }
  envelopes[0]->tick();
}
