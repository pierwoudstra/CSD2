#include "writeToFile.h"
#include "Delay.h"
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
    prev = 0.f;
    prevPrev = 0.f;
  }

  float process(float input) {
    output = (0.5f * input) - (0.5 * prevPrev);
    prevPrev = prev;
    prev = input;
    return output;
  }

private:
  float output;
  float prev;
  // kan met static float
  float prevPrev;
};

int main() {
  Delay delay = Delay(0.f, 5, 5, 1.f);
  FIR filter;

  // init write to file
  WriteToFile fileWriter("output.csv", true);

  float signal;

  // iterate per 100 Hz
  for (int j = 0; j < 24000; j += 240) {
    std::cout << j << std::endl;
    for (int i = 0; i < 24000; i++) {
      signal = sine(i, j);
      fileWriter.write(std::to_string( filter.process(signal)) + "\n");
    }
  }
}
