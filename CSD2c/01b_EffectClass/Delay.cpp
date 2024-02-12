#include "Delay.h"

Delay::Delay(float dryWetAmt, float delayTime)
    : Effect(dryWetAmt), buffer(sampleRate * delayTime) {
  this->delayTime = delayTime;
}

Delay::~Delay(){}

void Delay::prepare(float sampleRate) {
  this->sampleRate = sampleRate;
  buffer = CircBuffer(sampleRate * delayTime);

  for (int i = 0; i < delayTime * sampleRate; i++) {
    buffer.write(0.f);
  }
}

float Delay::processFrame(float input) {
  return buffer.read();
}
