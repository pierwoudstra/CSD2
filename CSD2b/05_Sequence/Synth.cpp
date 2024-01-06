#include "Synth.h"
#include <math.h>

Synth::Synth(float amplitude, float sampleRate) {
  this->amplitude = amplitude;
  this->sampleRate = sampleRate;
  phase = 0.f;
  increment = frequency / sampleRate;
}

Synth::~Synth() {
  delete oscillators[0];
  delete oscillators[1];
  delete oscillators[2];
  delete envelopes[0];
  delete envelopes[1];
}

void Synth::resetPhase() {
  phase = 0.f;
  envelopes[0]->resetPhase();
}

void Synth::stop() {
  phase = 0.f;
  increment = 0.f;
}

bool Synth::isPlaying() { return increment != 0.f; }

void Synth::setPitch(float midiNote) {
  std::cout << frequency << std::endl;
  frequency = midiToFrequency(midiNote);
  increment = frequency / sampleRate;
}

void Synth::setAmplitude(float amplitude) { this->amplitude = amplitude; }

float Synth::getSample() { return sample; }

float Synth::midiToFrequency(float midiNote) {
  return 440.f * pow(2.f, (midiNote - 69.0f) / 12.0f);
}
