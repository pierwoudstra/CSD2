#include "WaveTable.h"
#include <iostream>

#ifndef INC_03C_WAVE_TABLE_OSCILLATOR_OSCILLATOR_H
#define INC_03C_WAVE_TABLE_OSCILLATOR_OSCILLATOR_H

class Oscillator {
public:
  Oscillator(float frequency, float amplitude, float sampleRate);
  ~Oscillator();

  float getSample();
  void tick();

  void stop();
  bool isPlaying();

  void setFrequency(float frequency);
  void setAmplitude(float amplitude);

protected:
  std::string waveType;
  float frequency;
  float amplitude;
  float sampleRate;

  WaveTable *waveTable;
  float phase;
  float sample;
  float increment;
};

#endif // INC_03C_WAVE_TABLE_OSCILLATOR_OSCILLATOR_H
