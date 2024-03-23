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
  setEffectValue();
  tremolo.processFrame(input, output);
  delay.processFrame(output, output);
  waveshaper.processFrame(output, output);
  pitchShifter.processFrame(output, output);
  pitchShifter2.processFrame(output, output);
  chorus.processFrame(output, output);
  chorus2.processFrame(output, output);
  bitCrusher.processFrame(output, output);
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
