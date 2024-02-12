#include "writeToFile.h"
#include <math.h>
#include <iostream>

#define SAMPLE_RATE 48000
#define PI 3.14159265359

float sine(int time, float freq) {
  return sin(2 * PI * freq * time / SAMPLE_RATE);
}

class FIR {
public:
  FIR(){
    buffer = 0.f;
  }

  float process(float input) {
    output = 0.5f * input + 0.5f * buffer;
    buffer = input;
    return output;
  }

private:
  float output;
  float buffer;
};

int main() {
  FIR filter;

  // init write to file
  WriteToFile fileWriter("output.csv", true);

  float signal;

  // iterate per 100 Hz
  for (int j = 0; j < 24000; j += 100) {
    std::cout << j << std::endl;
    for (int i = 0; i < SAMPLE_RATE / 10; i++) {
      signal = sine(i, j);
      fileWriter.write(std::to_string( filter.process(signal)) + "\n");
    }
  }
}
