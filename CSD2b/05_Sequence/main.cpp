#include "DetunedSaw.h"
#include "FMSynth.h"
#include "KickSynth.h"
#include "Sine.h"
#include "jack_module.h"
#include "melody.h"
#include "Square.h"

#include <iostream>

/*
 * sounding sequence using Marc & Ciska's
 * code but with own classes
 */

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

class CustomCallback : public AudioCallback {
public:

  void updatePitch(Melody& melody, DetunedSaw& saw) {
    float note = melody.getNote();
    saw.setPitch(note);
  } // updatePitch()

  void prepare(int rate) override {
    sampleRate = (float)rate;
    updatePitch(melody, saw);
    std::cout << "\nsample rate: " << sampleRate << std::endl;
  }

  void process(AudioBuffer buffer) override {
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

private:
    float sampleRate = 44100;
    KickSynth kick = KickSynth(0.9f, sampleRate, 20.f, 20.f);
    DetunedSaw saw = DetunedSaw(0.9f, sampleRate, 50.f, 8.f);
    FMSynth fm = FMSynth(1.f, 44100, 48.0f, 7.7f, 20.f);

    Melody melody;
    int frameIndex = 0;

    /*
     * instead of using bpm and specifying note lengths we'll make every note
     * equal length and specify the delay between notes in terms of the
     * samplerate
     *
     * A note of say 500 msec or 0.5 sec, takes 0.5 * samplerate samples to be
     * played
     */

    double noteDelayFactor = 0.1;
  };

  int main() {

    auto callback = CustomCallback{};
    auto jackModule = JackModule{callback};

    jackModule.init(0, 1);

    bool running = true;
    while (running) {
      switch (std::cin.get()) {
      case 'q':
        running = false;
      }
    }

    // end the program
    return 0;
  }
