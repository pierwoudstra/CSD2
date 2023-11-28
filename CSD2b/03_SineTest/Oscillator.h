#ifndef OSCILLATOR_H
#define OSCILLATOR_H

class Oscillator {
public:
  // constructor & deconstructor
  Oscillator(int sampleRate, float frequency, float amplitude);
  ~Oscillator();

  // getters & setters
  void setFrequency(float frequency);
  float getFrequency();
  void setAmplitude(float amplitude);

protected:
  int sampleRate;
  float frequency;
  float amplitude;
  float phase;
};

#endif // OSCILLATOR_H
