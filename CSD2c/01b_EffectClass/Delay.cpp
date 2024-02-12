//
// Created by pirko on 09/02/2024.
//

#include "Delay.h"

Delay::Delay(float dryWetAmt, float delayTime) {
  this->delayTime = delayTime;

  buffer = CircBuffer(sampleRate * delayTime);

  // fill buffer with zeroes
  for (int i = 0; i < delayTime * sampleRate; i++) {
    buffer.write(0.f);
  }
}

Delay::~Delay(){}

void Delay::prepare(float sampleRate) {
  this->sampleRate = sampleRate;
}

float Delay::processFrame(float input) {
  return buffer.read();
}
