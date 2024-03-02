#include "Chorus.h"
#include "sine.h"
#include <iostream>

Chorus::Chorus(float dryWet, float modFreq, float modDepth, float samplerate) : Effect() {
  this->modDepth = modDepth;
  this->samplerate = samplerate;
  lfo = new Sine(modFreq, samplerate);
  delay = new Delay(0.f, 1, samplerate, 0.5f);
  setDryWet(dryWet);
}

Chorus::~Chorus() {
  // release dynamically allocated oscillator object.
  delete lfo;
  lfo = nullptr;

  delete delay;
  delay = nullptr;
}

void Chorus::prepare(float samplerate) {
  lfo->prepare(samplerate);
}

void Chorus::applyEffect(const float &input, float &output) {
  // normalize modulation signal
  float modSignal = lfo->genNextSample() + 1.f;
  modSignal *= 0.5f;
  modSignal *= modDepth;

  // adjust delay according to modulation signal
  delay->setNumDelaySamples(modSignal * (0.007 * samplerate));
  delay->applyEffect(input, output);
}

void Chorus::setModFrequency(float modFreq) {
  this->modFreq = modFreq;
  lfo->setFrequency(modFreq);
}

void Chorus::setModDepth(float modDepth){
  this->modDepth = modDepth;
}
