#include "writeToFile.h"
#include <math.h>

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

  // attempt at amplitude modulation
  for (int i = 0; i < SAMPLE_RATE / 2; i++) {
    signal = sine(i, 12000);
    fileWriter.write(std::to_string( filter.process(signal)) + "\n");
  }
}
