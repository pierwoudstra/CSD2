
#include <iostream>
#include "WaveTable.h"

#define PI 3.14159265359

WaveTable::WaveTable(std::string waveForm) {

  if (waveForm == "sine") {
    // generates sine wave
    for (int i = 0; i < tableSize; i++) {
      waveTable[i] = sin(2 * PI * i / tableSize);
    }
  } else if (waveForm == "saw") {
    // generates saw wave
    for (int i = 0; i < tableSize; i++) {
      waveTable[i] =  2.0f * ( float(i) / tableSize );
      if (waveTable[i] > 1.0f) {
        waveTable[i] -= 2.0f;
      }
    }
  } else if (waveForm == "square") {
    // generates square wave
    for (int i = 0; i < tableSize; i++) {
      if (i < int(tableSize / 2)) {
        waveTable[i] = 1.0f;
      } else {
        waveTable[i] = -1.0f;
      }
    }
  } else {
    // generates empty wave-table
    for (int i = 0; i < tableSize; i++) {
      waveTable[i] = 0;
    }
  }
}

WaveTable::~WaveTable() {}

float WaveTable::getWaveTableIndex(int index) {
  // returns value of index (index goes from 0 to 1024)
  return waveTable[index];
}
