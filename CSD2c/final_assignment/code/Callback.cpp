#include "Callback.h"
#include <iostream>

CustomCallback::~CustomCallback() {
  delete waveshaper;
  delete delay;
}

void CustomCallback::prepare(int rate) {
  samplerate = (float)rate;
  std::cout << "\nsamplerate: " << samplerate << "\n";
  //    chorus.prepare(samplerate);
  //    chorus2.prepare(samplerate);
}

void CustomCallback::initEffects() {
  waveshaper = new Waveshaper(1.f, Waveshaper::WaveshapeType::DIGITAL, 2.f);
  delay = new Delay(0.8f, 2048, 2048, 1.f);
}

double CustomCallback::mtof(float mPitch) {
  return 440.0 * pow(2.0, (mPitch - 69.0f) / 12.0f);
}

void CustomCallback::setOsc(float oscValue) {
  std::cout << "osc value changed" << std::endl;

  // map dry/wet from 0 - 360 to 0 - 1 - 0
  dryWet = (double((oscValue) / 360.f));

  std::cout << "CustomCallback::setDryWet: " << dryWet << std::endl;
  waveshaper->setDryWet(dryWet);
  delay->setDryWet(dryWet);
}

void CustomCallback::updatePitch(Melody &melody, Oscillator &myFastSine) {
  // Get the current note from the melody.
  float note = melody.getNote();

  // Convert the note to frequency.
  double freq = mtof(note);

  // Log the note and its frequency.
  std::cout << "next note: " << note << ", has frequency " << freq << std::endl;
  sine.setFrequency(freq);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels,
        numFrames] = buffer;

  for (int channel = 0u; channel < numInputChannels; channel++) {
    for (int i = 0u; i < numFrames; i++) {

      // set audio output
      float sample = sine.genNextSample();
      waveshaper->processFrame(sample, sample);
      delay->processFrame(sample, outputChannels[channel][i]);
      // pitchShifter.processFrame(sample, outputChannels[channel][i]);

      // bitCrusher.processFrame(sample, outputChannels[channel][i]);
      // pitchShifter.processFrame(sample, sample);
      // pitchShifter2.processFrame(sample, sample);

      if (frameIndex >= noteDelayFactor * samplerate) {
        // use melody to update pitch
        updatePitch(melody, sine);
        frameIndex = 0;
      } else {
        // Increment the frame index.
        frameIndex++;
      }
    }
  }
}
