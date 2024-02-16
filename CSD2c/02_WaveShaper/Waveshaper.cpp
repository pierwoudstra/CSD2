#include "waveshaper.h"
#include <math.h>

Waveshaper::Waveshaper(float dryWet, Waveshaper::WaveshapeType waveshapeType,
                       float drive)
    : Effect() {
  setDryWet(dryWet);
  this->waveshapeType = waveshapeType;
  this->drive = drive;
}

Waveshaper::~Waveshaper() {}

void Waveshaper::applyEffect(const float &input, float &output) {
  switch (waveshapeType) {
  case WaveshapeType::SOFT: {
    output = tanh(input * drive);
  }
  case WaveshapeType::HARD: {
    output = tanh(5 * input * drive);
  }
  case WaveshapeType::DIGITAL: {
    output = input * drive;
    if (output > 1) {
      output = 1.f;
    } else if (output < -1) {
      output = -1.f;
    }
  }
  case WaveshapeType::SINE: {
    output = sin(input * drive);
  }
  }
}

// setters
void Waveshaper::setDrive(float drive) {
  this->drive = drive;
}

void Waveshaper::setWaveshapeType(Waveshaper::WaveshapeType waveshapeType) {
  this->waveshapeType = waveshapeType;
}
