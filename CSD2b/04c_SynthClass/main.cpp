#include "DetunedSaw.h"
#include "FMSynth.h"
#include "KickSynth.h"
#include "jack_module.h"
#include "writeToFile.h"
#include <iostream>

/*
 * sounding wave-table oscillator using Ciska's
 * sounding code but with own classes
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
  void prepare(int rate) override {
    sampleRate = (float)rate;
    std::cout << "\nsample rate: " << sampleRate << std::endl;
  }

  void process(AudioBuffer buffer) override {
    auto [inputChannels, outputChannels, numInputChannels, numOutputChannels,
          numFrames] = buffer;

    for (int channel = 0; channel < numOutputChannels; ++channel) {
      for (int sample = 0; sample < numFrames; ++sample) {
        //
        outputChannels[channel][sample] = fm.getSample();
        kick.tick();
        saw.tick();
        fm.tick();
      }
    }
  }

private:
  float sampleRate = 44100;
  KickSynth kick = KickSynth(0.9f, sampleRate, 20.f, 40.f);
  DetunedSaw saw = DetunedSaw(0.9f, sampleRate, 60.f, 0.4f);
  FMSynth fm = FMSynth(1.f, 44100, 48.0f, 7.7f, 20.f);
};

int main() {

  FMSynth sound = FMSynth(1.f, 44100, 48.0f, 7.7f, 20.f);
  // init write to file
  WriteToFile fileWriter("output.csv", true);

  // attempt at amplitude modulation
  for (int i = 0; i < 44100; i++) {
    fileWriter.write(std::to_string(sound.getSample()) + "\n");
    sound.tick();
  }

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
