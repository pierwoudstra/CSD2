#include "Saw.h"

Saw::Saw(float frequency, float amplitude, int sampleRate)
    : Oscillator(frequency, amplitude, sampleRate) {
  waveTable = new WaveTable("saw");
}

Saw::~Saw() {}
