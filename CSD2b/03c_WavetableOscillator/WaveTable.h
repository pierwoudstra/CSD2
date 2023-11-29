#include <iostream>

#ifndef INC_03B_WAVETABLEGENERATOR_WAVETABLE_H
#define INC_03B_WAVETABLEGENERATOR_WAVETABLE_H

class WaveTable {
public:
  WaveTable(std::string waveForm);
  ~WaveTable();

  float getWaveTableIndex(int index);
protected:
  constexpr static int tableSize = 1024;
  float waveTable[tableSize];
};

#endif // INC_03B_WAVETABLEGENERATOR_WAVETABLE_H
