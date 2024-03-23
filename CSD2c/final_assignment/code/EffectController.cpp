#include "EffectController.h"

EffectController::EffectController() { setEffectValue(); }
EffectController::~EffectController() {}

void EffectController::prepare(float samplerate) {
  this->samplerate = samplerate;
  std::cout << "\nsamplerate: " << samplerate << "\n";
  tremolo.prepare(samplerate);
  chorus.prepare(samplerate);
  chorus2.prepare(samplerate);
}

void EffectController::processFrame(const float &input, float &output) {
  float sample = 0;
  setEffectValue();
  tremolo.processFrame(input, sample);
  delay.processFrame(sample, sample);
  waveshaper.processFrame(sample, sample);
  pitchShifter.processFrame(sample, sample);
  pitchShifter2.processFrame(sample, sample);
  chorus.processFrame(sample, sample);
  chorus2.processFrame(sample, sample);
  bitCrusher.processFrame(sample, output);
}

void EffectController::setCompassValue(int compassValue) {
  this->compassValue = compassValue;
  setEffectValue();
}

void EffectController::setEffectValue() {
  tremolo.setDryWet(float(compassValue / 360.f));
  delay.setDryWet(float(compassValue / 360.f));
  waveshaper.setDryWet(float(compassValue / 360.f));
  pitchShifter.setDryWet(float(compassValue / 360.f));
  pitchShifter2.setDryWet(float(compassValue / 360.f));
  chorus.setDryWet(float(compassValue / 360.f));
  chorus2.setDryWet(float(compassValue / 360.f));
  bitCrusher.setDryWet(float(compassValue / 360.f));
}
