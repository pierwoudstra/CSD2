#include "Sine.h"

Sine::Sine(float frequency, float amplitude, int sampleRate)
    : Oscillator(frequency, amplitude, sampleRate) {
  waveTable = new WaveTable("sine");
}

Sine::~Sine() {}
