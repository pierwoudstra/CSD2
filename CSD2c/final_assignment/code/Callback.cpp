#include "Callback.h"
#include <iostream>

CustomCallback::~CustomCallback() {
  delete waveshaper;
  delete delay;
}

void CustomCallback::prepare(int rate) {
  samplerate = (float)rate;
  std::cout << "\nsamplerate: " << samplerate << "\n";
}

void CustomCallback::initEffects() {
    pitchShifter = new PitchShifter(0.f, 1.3f);
    bitCrusher = new BitCrusher(4.0, 1.f);
    waveshaper = new Waveshaper(1.f, Waveshaper::WaveshapeType::DIGITAL, 2.f);
    delay = new Delay(0.8f, 2048, 2048, 1.f);
}


void CustomCallback::setOsc(float compass, float gravityX, float gravityY) {
  // map compass from 0 - 360 to dryWet 0 - 1 - 0
  dryWet = (float((compass) / 360.f));
  std::cout << "CustomCallback::setDryWet: " << dryWet << std::endl;
  waveshaper->setDryWet(dryWet);
  delay->setDryWet(dryWet);

  // map gravityX from -1 - 0 to feedback 0 - 1
  feedback = (float((gravityX + 1) / 2.f));
  std::cout << "CustomCallback::setFeedback: " << feedback << std::endl;
  delay->setFeedback(feedback);

    // map gravityY from -1 - 0 to QuantizedBitDepth 0 - 20
  QuantizedBitDepth = (double((gravityY + 1) * 10.f));
  std::cout << "CustomCallback::setQuantizedBitDepth: " << QuantizedBitDepth << std::endl;
  bitCrusher->setQuantizedBitDepth(QuantizedBitDepth);
}

void CustomCallback::updatePitch(Melody &melody, Oscillator &myFastSine) {
  // Get the current note from the melody.
  float note = melody.getNote();

  // Convert the note to frequency.
  double freq = 440.0 * pow(2.0, (note - 69.0f) / 12.0f);

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
      pitchShifter->processFrame(sample, sample);
      bitCrusher->processFrame(sample, sample);
      waveshaper->processFrame(sample, sample);
      delay->processFrame(sample, outputChannels[channel][i]);

      if (frameIndex >= noteDelayFactor * samplerate) {
        updatePitch(melody, sine);
        frameIndex = 0;
      } else {
        frameIndex++;
      }
    }
  }
}
