#include "WaveTable.h"
#include "Oscillator.h"
#include "writeToFile.h"

int main() {

  // WaveTable class generates lookup tables
  // Oscillator class is used to play the wave-table

  // TODO WaveTable class works but Oscillator class still needs implementation

  WaveTable sine("sine");
  WaveTable saw("saw");
  WaveTable square("square");

  // init write to file
  WriteToFile fileWriter("output.csv", true);

  // attempt at amplitude modulation
  for (int i = 0; i < 1024; i++) {
    fileWriter.write(std::to_string(square.getWaveTableIndex(i)) + "\n");
  }

}
