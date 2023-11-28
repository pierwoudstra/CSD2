#include "WaveTable.h"
#include "writeToFile.h"

int main() {

  // goal is to generate different wave-tables
  // with length of 1024 samples

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
