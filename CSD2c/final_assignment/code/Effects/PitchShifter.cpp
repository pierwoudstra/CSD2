#include "PitchShifter.h"

PitchShifter::PitchShifter(float dryWet, float shift) : Effect() {
  setDryWet(dryWet);
  this->shift = shift;

  writeHead = 0;
  readHead = 0.f;

  crossFade = 1.f;
  buffer = new float[bufSize];
}

PitchShifter::~PitchShifter() {}

void PitchShifter::applyEffect(const float &input, float &output) {

  // should filter input for better effect

  // write to circular buffer
  buffer[writeHead] = input;

  // read fractional readHead and generate 0 and 180 degree readHead in integer
  // form
  int readHeadInt1 = int(readHead);
  int readHeadInt2 = 0;
  if (readHeadInt1 >= bufSize / 2) {
    readHeadInt2 = readHeadInt1 - (bufSize / 2);
  } else {
    readHeadInt2 = readHeadInt1 + (bufSize / 2);
  }

  // read the two samples
  float sample1 = (float)buffer[readHeadInt1];
  float sample2 = (float)buffer[readHeadInt2];

  // check if first readHead starts overlap with write head?
  // if yes -> do crossFade to second readHead
  if (overlap >= (writeHead - readHeadInt1) &&
      (writeHead - readHeadInt1) >= 0 && shift != 1.f) {
    int rel = writeHead - readHeadInt1;
    crossFade = ((float)rel) / ((float)overlap);
  } else if (writeHead - readHeadInt1 == 0) {
    crossFade = 0.f;
  }

  // check if second readHead starts overlap with write head?
  // if yes -> do crossFade to first readHead
  if (overlap >= (writeHead - readHeadInt2) &&
      (writeHead - readHeadInt2) >= 0 && shift != 1.f) {
    int rel = writeHead - readHeadInt2;
    crossFade = 1.f - ((float)rel) / ((float)overlap);
  } else if (writeHead - readHeadInt2 == 0) {
    crossFade = 1.f;
  }

  // do cross-fading and sum
  float sum = (sample1 * crossFade + sample2 * (1.f - crossFade));

  // increment fractional readHead and writeHead
  readHead += shift;
  writeHead++;
  if (writeHead == bufSize)
    writeHead = 0;
  if (int(readHead) >= bufSize)
    readHead = 0.f;

  output = sum;
}

void PitchShifter::setPitch(float shift) {
  this->shift = shift;
}
