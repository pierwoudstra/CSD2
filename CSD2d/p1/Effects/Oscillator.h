#ifndef OSCILLATOR_H
#define OSCILLATOR_H

class Oscillator {
public:
  // constructor & deconstructor
  Oscillator(float sampleRate = 44100, float frequency = 4.f, float amplitude = 1.f) {
    this->sampleRate = sampleRate;
    this->frequency = frequency;
    this->amplitude = amplitude;

    phase = 0.0f;
  }

  ~Oscillator() {}

  // getters & setters
  void setFrequency(float frequency) {
    if (this->frequency > 0 && this->frequency < sampleRate / 2) {
      this->frequency = frequency;
    }
  }
  float getFrequency() { return frequency; }
  void setAmplitude(float amplitude) { this->amplitude = amplitude; }
  float getAmplitude() { return amplitude; }

protected:
  float sampleRate;
  float frequency;
  float amplitude;
  float phase;
};

#endif // OSCILLATOR_H
