#include <iostream>
#include <math.h>
#include "Oscillator.h"

Oscillator::Oscillator(std::string waveType, float frequency, float amplitude, int sampleRate) {
  waveTable = new WaveTable(waveType);
  this->frequency = frequency;
  this->amplitude = amplitude;
  this->sampleRate = sampleRate;
  phase = 0;
  sample = 0;
}

Oscillator::~Oscillator() {}


// methods for playing oscillator

float Oscillator::getSample() {
  return sample;
}

void Oscillator::tick() {
  // update phase
  phase += frequency / sampleRate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }

  // update sample
  sample = waveTable->getWaveTableIndex(floor(phase * 1024.0f));
}


// getters & setters

void Oscillator::setFrequency(float frequency) {
  if (this->frequency > 0 && this->frequency < sampleRate / 2) {
    this->frequency = frequency;
  }
}

void Oscillator::setAmplitude(float amplitude) {
  if (this->amplitude < 1.0f && this->amplitude > -1.0f) {
    this->amplitude = amplitude;
  }
}
