#include "Oscillator.h"

// constructor & deconstructor

Oscillator::Oscillator(int sampleRate, float frequency, float amplitude) {
  this->sampleRate = sampleRate;
  this->frequency = frequency;
  this->amplitude = amplitude;

  phase = 0.0f;
}

Oscillator::~Oscillator() {}

// getters & setters

void Oscillator::setFrequency(float frequency) {
  if (this->frequency > 0 && this->frequency < sampleRate / 2) {
    this->frequency = frequency;
  }
}

float Oscillator::getFrequency() { return frequency; }

void Oscillator::setAmplitude(float amplitude) { this->amplitude = amplitude; }
