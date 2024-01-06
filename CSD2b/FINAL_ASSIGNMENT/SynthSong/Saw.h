
#include "Oscillator.h"

#ifndef INC_04C_SYNTHCLASS_SAW_H
#define INC_04C_SYNTHCLASS_SAW_H

class Saw : public Oscillator {
public:
  Saw(float frequency, float amplitude, int sampleRate);
  ~Saw();
};

#endif // INC_04C_SYNTHCLASS_SAW_H
