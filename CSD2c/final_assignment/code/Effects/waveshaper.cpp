#include "Waveshaper.h"
#include <iostream>
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
    // subtle clipping
    output = tanh(input * drive) / tanh(drive);
  }
  case WaveshapeType::HARD: {
    // hard clipping
    output = tanh(5 * input * drive) / tanh(5 * drive);
  }
  case WaveshapeType::DIGITAL: {
    // basic digital clipping
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
void Waveshaper::setDrive(float drive) { this->drive = drive; }

void Waveshaper::setWaveshapeType(Waveshaper::WaveshapeType waveshapeType) {
  this->waveshapeType = waveshapeType;
}
