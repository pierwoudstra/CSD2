#include "EffectController.h"

EffectController::EffectController()
{
    std::cout << "EffectController Constructor" << std::endl;
    setEffectValue(dryWet);
}

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
    tremolo.processFrame(input, sample);
    waveshaper.processFrame(sample, sample);
    bitCrusher.processFrame(sample, sample);
    pitchShifter.processFrame(sample, sample);
    pitchShifter2.processFrame(sample, sample);
    delay.processFrame(sample, output);
    // chorus.processFrame(sample, sample);
    // chorus2.processFrame(sample, output);
}


void EffectController::setDryWet(float compassValue) {
    dryWet = (float(compassValue / 180.f));
}

void EffectController::setEffectValue(float oscValue) {;
    dryWet = (float(oscValue / 360.f));
    std::cout << "DryWet: " << dryWet << std::endl;
    tremolo.setDryWet(dryWet);
  delay.setDryWet(dryWet);
  waveshaper.setDryWet(dryWet);
  pitchShifter.setDryWet(dryWet);
  pitchShifter2.setDryWet(dryWet);
  chorus.setDryWet(dryWet);
  chorus2.setDryWet(dryWet);
  bitCrusher.setDryWet(dryWet);
}
