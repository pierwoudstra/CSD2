#include "writeToFile.h"
#include <math.h>
#include <iostream>
#include "Filters.h"

#define SAMPLE_RATE 48000
#define PI 3.14159265359

float sine(int time, float freq) {
  return sin(2 * PI * freq * time / SAMPLE_RATE);
}

int main() {

  Biquad filter;
  filter.setCoefficients(
      -1.996174898187567,
      0.9979155096954627,
      0.00043515287697386376,
      0.0008703057539477275,
      0.00043515287697386376


      );

  // init write to file
  WriteToFile fileWriter("output.csv", true);

  float signal;
  float output;

  // iterate per 100 Hz
  for (int j = 0; j < 24000; j += 100) {
    std::cout << j << std::endl;
    for (int i = 0; i < 100; i++) {
      signal = sine(i, j);
      output = filter.process(signal);
      fileWriter.write(std::to_string(output) + "\n");
    }
  }
}
