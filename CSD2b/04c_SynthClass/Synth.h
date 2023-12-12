#include "Envelope.h"
#include "Oscillator.h"

#ifndef INC_04C_SYNTHCLASS_SYNTH_H
#define INC_04C_SYNTHCLASS_SYNTH_H

class Synth {
public:
  Synth(float amplitude, float sampleRate);
  ~Synth();

  virtual void tick() = 0; // tick method depends on type of synth
  void resetPhase();
  void stop();
  bool isPlaying(); // method to check if synth is playing
  void setPitch(float midiNote);
  void setAmplitude(float amplitude);
  float getSample(); // returns current sample

protected:
  float sampleRate;
  float phase;     // phase refers to phase of amplitude envelope
  float frequency; // frequency in Hz
  float amplitude;
  float increment; // increment is calculated in constructor
  float sample;    // output sample

  Envelope *envelopes[2]; // two envelopes (don't have to be used both)

  Oscillator *oscillators[3]; // oscillator bank

  float midiToFrequency(float midiNote); // returns frequency in Hz
};

#endif // INC_04C_SYNTHCLASS_SYNTH_H
