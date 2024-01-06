#include "Callback.h"

void CustomCallback::updatePitch(Melody& melody, DetunedSaw& saw) {
  float note = melody.getNote();
  saw.setPitch(note);
} // updatePitch()

void CustomCallback::prepare(int rate) {
  sampleRate = (float)rate;
  updatePitch(melody, saw);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels,
        numFrames] = buffer;

  for (int channel = 0; channel < numOutputChannels; ++channel) {
    for (int sample = 0; sample < numFrames; ++sample) {
      //

      outputChannels[channel][sample] = saw.getSample();
      saw.tick(); // rather mixed up functionality

      /*
         * After every sample, check if we need to advance to the next note
         * This is a bit awkward in this scheme of buffers per channel
         *  In a multichannel setting we should update pitches independently per
         * channel!
       */

      if (frameIndex >= noteDelayFactor * sampleRate) {
        // reset frameIndex
        frameIndex = 0;
        updatePitch(melody, saw);
      } else {
        // increment frame index
        frameIndex++;
      }
    }
  }
}
