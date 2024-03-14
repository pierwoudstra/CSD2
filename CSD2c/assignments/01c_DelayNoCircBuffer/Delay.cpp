#include "Delay.h"
#include <iostream>

Delay::Delay(float feedback, int numDelaySamples, int maxDelaySize, float wet)
    : Effect(wet), feedback(0.5f), numDelaySamples(2048), maxDelaySize(2048),
      readHead(0), writeHead(0) {
  // validate delay time < max delay time
  if (numDelaySamples > maxDelaySize) {
    std::cout << "delay time larger than max delay time" << std::endl;
  }
  setFeedback(feedback);
  setNumDelaySamples(numDelaySamples);

  buffer = new float[maxDelaySize];

  /*for (int i = 0; i < maxDelaySize; i++) {
    buffer[i] = 0.f;
  }*/
}

Delay::~Delay() {}

float Delay::applyEffect(float input) {
  // read value from buffer, increment & wrap
  output = buffer[readHead];
  readHead++;
  wrapHead(readHead);

  // write value to buffer, increment & wrap
  buffer[writeHead] = output * feedback + input;
  writeHead++;
  wrapHead(writeHead);

  return output;
}

void Delay::setNumDelaySamples(int numDelaySamples) {
  this->numDelaySamples = numDelaySamples;
  readHead = writeHead - numDelaySamples + maxDelaySize;
  wrapHead(readHead);
}

void Delay::setFeedback(float feedback) {
  this->feedback = feedback;
  if (feedback < 0.f || feedback > 1.f) {
    std::cout << "feedback is too high or too low" << std::endl;
    feedback = 0.f;
  }
}
