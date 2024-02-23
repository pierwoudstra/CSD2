#include "callback.h"
#include <iostream>

void CustomCallback::prepare(int rate) {
  samplerate = (float)rate;
  std::cout << "\nsamplerate: " << samplerate << "\n";
  tremolo.prepare(rate);
  delay.prepare(rate);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels,
        numFrames] = buffer;
  float sample;
  for (int channel = 0u; channel < numInputChannels; channel++) {
    for (int i = 0u; i < numFrames; i++) {
      // tremolo.processFrame(inputChannels[channel][i], sample);
      // waveshaper.processFrame(sample, sample);
      chorus.processFrame(inputChannels[channel][i], outputChannels[0][i]);
      chorus.processFrame(inputChannels[channel][i], outputChannels[1][i]);
    }
  }
}
