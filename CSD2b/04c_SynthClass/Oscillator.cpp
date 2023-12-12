#include "Oscillator.h"
#include <iostream>
#include <math.h>

Oscillator::Oscillator(float frequency, float amplitude, int sampleRate) {
  this->frequency = frequency;
  this->amplitude = amplitude;
  this->sampleRate = sampleRate;
  phase = 0.f;
  sample = 0.f;
  increment = frequency / sampleRate;
}

Oscillator::~Oscillator() { delete waveTable; }

// methods for playing oscillator

float Oscillator::getSample() { return sample; }

void Oscillator::tick() {
  // update phase
  phase += increment;
  if (phase > 1.0f) {
    phase -= 1.0f;
  }

  // update sample
  sample = waveTable->getWaveTableIndex(floor(phase * 1024.0f));
}

void Oscillator::stop() {
  // stops the increment
  // maybe it's better to set the amplitude to 0?
  // but this works with the isPlaying() method
  phase = 0.f;
  increment = 0.f;
}

bool Oscillator::isPlaying() { return increment != 0.f; }

// getters & setters

void Oscillator::setFrequency(float frequency) {
  if (this->frequency > 0 && this->frequency < sampleRate / 2) {
    this->frequency = frequency;
    increment = frequency / sampleRate;
  }
}

void Oscillator::setAmplitude(float amplitude) {
  if (this->amplitude < 1.0f && this->amplitude > -1.0f) {
    this->amplitude = amplitude;
  }
}
