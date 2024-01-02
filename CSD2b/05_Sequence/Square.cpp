#include "Square.h"

Square::Square(float frequency, float amplitude, int sampleRate)
    : Oscillator(frequency, amplitude, sampleRate) {
  waveTable = new WaveTable("square");
}

Square::~Square() {}
