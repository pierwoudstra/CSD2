#include "KickSynth.h"
#include "DetunedSaw.h"
#include "jack_module.h"
#include "writeToFile.h"
#include <iostream>
#include <math.h>

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

        outputChannels[channel][sample] = kick.getSample() + saw.getSample();
        kick.tick();
        saw.tick();
      }
    }
  }

private:
  float sampleRate = 44100;
  KickSynth kick = KickSynth(0.9f, sampleRate, 20.f, 40.f);
  DetunedSaw saw = DetunedSaw( 0.9f, sampleRate, 60.f, 0.4f );
};

int main() {

  DetunedSaw kick = DetunedSaw(0.9f, 44100, 20.f, 0.4f);
  // init write to file
  WriteToFile fileWriter("output.csv", true);

  // attempt at amplitude modulation
  for (int i = 0; i < 44100; i++) {
    fileWriter.write(std::to_string(kick.getSample()) + "\n");
    kick.tick();
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
