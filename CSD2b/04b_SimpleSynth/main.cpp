#include "Oscillator.h"
#include "Envelope.h"
#include "jack_module.h"
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
    for (int i = 0; i < buffer.numFrames; ++i) {

      // modulate frequency with output of modulator synth
      sinOsc.setFrequency(220.0f + (modulator.getSample() * 50.0f));

      //
      float output = sinOsc.getSample() * env.getValue();

      buffer.outputChannels[0][i] = output;
      sinOsc.tick();
      modulator.tick();
      env.tick();
    }
  }

private:
  float sampleRate = 44100;
  Oscillator squareOsc = Oscillator("square", 220.0f, 0.5f, sampleRate);
  Oscillator sinOsc = Oscillator("sine", 220.0f, 0.7f, sampleRate);
  Oscillator modulator = Oscillator("saw", 133.0f, 1.0f, sampleRate);
  Envelope env = Envelope(sampleRate);
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
