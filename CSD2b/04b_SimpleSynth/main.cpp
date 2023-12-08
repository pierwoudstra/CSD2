#include "Oscillator.h"
#include "Envelope.h"
#include "jack_module.h"
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
    for (int i = 0; i < buffer.numFrames; ++i) {

      // modulate frequency with output of modulator synth
      sinOsc.setFrequency(220.f + (modulator.getSample() * 50.0f));

      squareOsc.setFrequency(55.f + (freqEnv.getValue() * 700.f));

      //
      float hardcoreKick = tanh((squareOsc.getSample() + ( overTone.getSample() * 0.1f )) * ampEnv.getValue() * 70.f) * 0.8f;

      buffer.outputChannels[0][i] = hardcoreKick;
      sinOsc.tick();
      modulator.tick();
      ampEnv.tick();
      freqEnv.tick();
      squareOsc.tick();
      overTone.tick();
    }
  }

private:
  float sampleRate = 44100;
  Oscillator squareOsc = Oscillator("sine", 220.0f, 0.5f, sampleRate);
  Oscillator overTone = Oscillator("square", 1100.0f, 0.5f, sampleRate);
  Oscillator sinOsc = Oscillator("sine", 220.0f, 0.7f, sampleRate);
  Oscillator modulator = Oscillator("saw", 133.0f, 1.0f, sampleRate);
  Envelope ampEnv = Envelope(0.05f, 0.6f, true, sampleRate / 3);
  Envelope freqEnv = Envelope(0.f, 0.07f, true, sampleRate / 3);
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
