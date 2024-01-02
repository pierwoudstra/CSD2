
#include "Oscillator.h"

#ifndef INC_04C_SYNTHCLASS_SINE_H
#define INC_04C_SYNTHCLASS_SINE_H

class Sine : public Oscillator {
public:
  Sine(float frequency, float amplitude, int sampleRate);
  ~Sine();
};

#endif // INC_04C_SYNTHCLASS_SINE_H
