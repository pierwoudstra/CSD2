#include "Callback.h"
#include <iostream>

void CustomCallback::prepare(int rate) {
  samplerate = (float)rate;
  std::cout << "\nsamplerate: " << samplerate << "\n";
}

double CustomCallback::mtof(float mPitch)
{
  return 440.0 * pow(2.0, (mPitch - 69.0f) / 12.0f);
}

void CustomCallback::updatePitch(Melody& melody, Oscillator& myFastSine) 
{
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
    outputChannels[channel][i] = sine.genNextSample();
    if(frameIndex >= noteDelayFactor * samplerate) {
      updatePitch(melody, sine);
      frameIndex = 0;
    }
    else {
      // Increment the frame index.
      frameIndex++;
      }
    }
  }
}
