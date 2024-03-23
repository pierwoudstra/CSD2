#include "EffectController.h"

EffectController::EffectController() {
  std::cout << "EffectController Constructor" << std::endl;
  setEffectValue(dryWet);
}

EffectController::~EffectController() {}

void EffectController::prepare(float samplerate) {
  this->samplerate = samplerate;
  std::cout << "\nsamplerate: " << samplerate << "\n";
  chorus.prepare(samplerate);
  chorus2.prepare(samplerate);
}

void EffectController::processFrame(const float &input, float &output) {
  float sample;
  waveshaper.processFrame(input, sample);
  bitCrusher.processFrame(sample, sample);
  pitchShifter.processFrame(sample, sample);
  pitchShifter2.processFrame(sample, sample);
  delay.processFrame(sample, output);
}

void EffectController::setDryWet(float compassValue) {
  dryWet = (float(compassValue / 360.f));
  std::cout << "DryWet: " << dryWet << std::endl;
  waveshaper.setDryWet(1.f);
  bitCrusher.setDryWet(1.f);
  pitchShifter.setDryWet(1.f);
  pitchShifter2.setDryWet(1.f);
  delay.setDryWet(1.f);
}

void EffectController::setEffectValue(float oscValue) {
  setDryWet(oscValue);
}
