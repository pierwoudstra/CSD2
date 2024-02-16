#include "callback.h"
#include <iostream>

void CustomCallback::prepare(int rate) {
  // retrieving user info
  std::cout << "do u want 2 hear the tremolo?" << std::endl;
  tremoloOn = ui.retrieveValueInRange(0, 1);
  std::cout << "do u want 2 hear the delay?" << std::endl;
  delayOn = ui.retrieveValueInRange(0, 1);
  std::cout << "do u want 2 hear the waveshaper?" << std::endl;
  waveshaperOn = ui.retrieveValueInRange(0, 1);

  if (tremoloOn == 0) {
    tremolo.setBypass(true);
  }
  if (delayOn == 0) {
    delay.setBypass(true);
  }
  if (waveshaperOn == 0) {
    waveshaper.setBypass(true);
  }

  samplerate = (float)rate;
  std::cout << "\nsamplerate: " << samplerate << "\n";
  tremolo.prepare(rate);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels,
        numFrames] = buffer;
  float sample;
  for (int channel = 0u; channel < numInputChannels; channel++) {
    for (int i = 0u; i < numFrames; i++) {
      tremolo.processFrame(inputChannels[channel][i], sample);
      waveshaper.processFrame(sample, sample);
      delay.processFrame(sample, outputChannels[channel][i]);
    }
  }
}
