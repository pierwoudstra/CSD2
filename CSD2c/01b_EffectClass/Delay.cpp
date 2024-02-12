#include "Delay.h"

Delay::Delay(float dryWetAmt, float delayTime)
    : Effect(dryWetAmt), buffer(sampleRate * delayTime * 2) {
  this->delayTime = delayTime;
}

Delay::~Delay(){}

void Delay::prepare(float sampleRate) {
  this->sampleRate = sampleRate;
  buffer = CircBuffer(int(sampleRate * delayTime * 2));

  for (int i = 0; i < delayTime * sampleRate * 2; i++) {
    buffer.write(0.f);
  }
}

float Delay::processFrame(float input) {
  buffer.write(input);
  buffer.setReadHead(-(delayTime * sampleRate));
  wetOutput = buffer.read();
  return ((1 - dryWetAmt) * input) + (dryWetAmt * wetOutput);;
}
