#include "WaveTable.h"
#include <iostream>

#ifndef INC_03C_WAVE_TABLE_OSCILLATOR_OSCILLATOR_H
#define INC_03C_WAVE_TABLE_OSCILLATOR_OSCILLATOR_H

class Oscillator {
public:
  Oscillator(std::string waveType, float frequency, float amplitude,
             int sampleRate);
  ~Oscillator();

  float getSample();
  void tick();

  void setFrequency(float frequency);
  void setAmplitude(float amplitude);

private:
  std::string waveType;
  float frequency;
  float amplitude;
  int sampleRate;

  WaveTable *waveTable;
  float phase;
  float sample;
};

#endif // INC_03C_WAVE_TABLE_OSCILLATOR_OSCILLATOR_H
