#include "writeToFile.h"
#include "delay.h"
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
  Delay delay = Delay(0.f, 1, 1, 1.f);
  FIR filter;

  // init write to file
  WriteToFile fileWriter("output.csv", true);

  float signal;
  float output;
  float prevOutput = 0.f;

  // iterate per 100 Hz
  for (int i = 0; i < 24000; i++) {
    signal = abs(sine(i, 100));
    delay.processFrame(signal, output);
    output = signal - output + (0.995 * prevOutput);
    prevOutput = output;
    fileWriter.write(std::to_string(output) + "\n");
  }
}
