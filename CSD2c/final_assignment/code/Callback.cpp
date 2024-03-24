#include "Callback.h"
#include <iostream>

void CustomCallback::prepare(int rate) {
  samplerate = (float)rate;
    this->samplerate = samplerate;
    std::cout << "\nsamplerate: " << samplerate << "\n";
    chorus.prepare(samplerate);
    chorus2.prepare(samplerate);
}

double CustomCallback::mtof(float mPitch) {
  return 440.0 * pow(2.0, (mPitch - 69.0f) / 12.0f);
}

void CustomCallback::setOsc(float oscValue) {
  std::cout << "osc value changed" << std::endl;
  this->oscValue = oscValue;
  setDryWet(oscValue);
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

void CustomCallback::setDryWet(float compassValue) {
    dryWet = (float((compassValue + 180.f) / 360.f));
//  std::cout << "DryWet: " << dryWet << std::endl;
    waveshaper.setDryWet(dryWet);
  bitCrusher.setDryWet(dryWet);
    pitchShifter.setDryWet(dryWet);
    pitchShifter2.setDryWet(dryWet);
    delay.setDryWet(dryWet);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels,
        numFrames] = buffer;
  for (int channel = 0u; channel < numInputChannels; channel++) {
    for (int i = 0u; i < numFrames; i++) {

      // set audio output
        float sample = sine.genNextSample();
//      outputChannels[channel][i] = sample;
        waveshaper.processFrame(sample, sample);
      bitCrusher.processFrame(sample, sample);
      pitchShifter.processFrame(sample, sample);
      pitchShifter2.processFrame(sample, sample);
        delay.processFrame(sample, outputChannels[channel][i]);
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
