#include "EffectController.h"

EffectController::EffectController() {
  std::cout << "EffectController Constructor" << std::endl;
  setEffectValue(0.f);
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
  waveshaper.setDryWet(0.f);
  bitCrusher.setDryWet(0.f);
  pitchShifter.setDryWet(0.f);
  pitchShifter2.setDryWet(0.f);
  delay.setDryWet(0.f);
}

void EffectController::setEffectValue(float oscValue) {
  setDryWet(oscValue);
}
