// using Daan's Moog Ladder filter!
#include "Effect.h"
#include <cmath>

// idea for most of this code from YT channel:
// YetAnotherElectronicsChannel
// title of video:
// [#7] Pitch Shifting - Audio DSP On STM32 (24 Bit / 96 kHz)

#define bufSize 1000
#define overlap 100

#ifndef INC_03_PRESENTATION_PITCHSHIFTER_H
#define INC_03_PRESENTATION_PITCHSHIFTER_H

class PitchShifter : public Effect {
public:
  PitchShifter(float dryWet = 1.f, float shift = 2.f) {

    oldShiftValue = 0.f;
    //
    //    // initializing the filter
    //    filter = MoogLadder();
    //    filter.prepare(44100);
    //    filter.setCoefficients(MoogLadder::makeHiPass12());
    //    filter.setCriticalFrequency(300.0);
    //    filter.setResonance(0);
    //
    //    // initializing the filter
    //    lowPass = MoogLadder();
    //    filter.prepare(44100);
    //    lowPass.setCoefficients(MoogLadder::makeLoPass24());
    //    lowPass.setCriticalFrequency(22000.0);
    //    lowPass.setResonance(0);

    this->shift = shift;

    writeHead = 0;
    readHead = 0.f;

    crossFade = 1.f;
    buffer = new float[bufSize];
    for (int i = 0; i < bufSize; i++) {
      buffer[i] = 0.f;
    }
  }
  ~PitchShifter() {
    //    delete buffer;
  }

  // calculating semitones to playback speed
  float semitoneToSpeed(float semitones) {
    // 2.f^(semitones / 12.f)
    return std::pow(2.f, (semitones / 12.f));
  }

  float smoothParameterChange(float oldValue, float newValue) {
    // adjust the factor based on how quickly you want the parameter to change
    const float smoothingFactor = 0.1f;
    return oldValue + smoothingFactor * (newValue - oldValue);
  }

  void applyEffect(const float &input, float &output) override {

    // using Daan's filter to high-pass the input
    // auto filteredInput = float(filter.process(double(input)));

    // write to circular buffer
    buffer[writeHead] = input;

    // read fractional readHead and generate 0 and 180 degree readHead in
    // integer form
    int readHeadInt1 = std::round(readHead);
    int readHeadInt2 = 0;
    if (readHeadInt1 >= bufSize / 2) {
      readHeadInt2 = readHeadInt1 - (bufSize / 2);
    } else {
      readHeadInt2 = readHeadInt1 + (bufSize / 2);
    }

    // read the two samples
    auto sample1 = (float)buffer[readHeadInt1];
    auto sample2 = (float)buffer[readHeadInt2];

    // check if first readHead starts overlap with write head?
    // if yes -> do crossFade to second readHead
    if (overlap >= (writeHead - readHeadInt1) &&
        (writeHead - readHeadInt1) >= 0 && semitoneToSpeed(shift) != 1.f) {
      int rel = writeHead - readHeadInt1;
      crossFade = float(((float)rel) / ((float)overlap));
    } else if (writeHead - readHeadInt1 == 0) {
      crossFade = 0.f;
    }

    // check if second readHead starts overlap with write head?
    // if yes -> do crossFade to first readHead
    if (overlap >= (writeHead - readHeadInt2) &&
        (writeHead - readHeadInt2) >= 0 && semitoneToSpeed(shift) != 1.f) {
      int rel = writeHead - readHeadInt2;
      crossFade = 1.f - float(((float)rel) / ((float)overlap));
    } else if (writeHead - readHeadInt2 == 0) {
      crossFade = 1.f;
    }

    // do cross-fading and sum
    float sum = (sample1 * crossFade) + (sample2 * (1.f - crossFade));

    // increment fractional readHead and writeHead
    readHead += semitoneToSpeed(shift);
    writeHead++;
    if (writeHead == bufSize)
      writeHead = 0;
    if (int(readHead) >= bufSize)
      readHead = 0.f;

    //     double filteredOutput = lowPass.process(double(sum));

    output = float(sum);
  }

  void setPitch(float newShiftValue) {
    shift = smoothParameterChange(oldShiftValue, newShiftValue);

    oldShiftValue = shift;
  }

private:
  //  MoogLadder filter;
  //  MoogLadder lowPass;

  float *buffer;
  int writeHead;
  float readHead;
  float shift;
  float crossFade;

  float oldShiftValue;
};

#endif // INC_03_PRESENTATION_PITCHSHIFTER_H
