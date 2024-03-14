#include "Delay.h"

Delay::Delay(float wet, float delayTime)
    : Effect(wet), buffer(sampleRate * delayTime * 2) {
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

float Delay::applyEffect(float input) {
  buffer.write(input);
  buffer.setReadHead(-(delayTime * sampleRate));
  return buffer.read();
}
