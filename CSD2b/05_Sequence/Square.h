
#include "Oscillator.h"

#ifndef INC_04C_SYNTHCLASS_SQUARE_H
#define INC_04C_SYNTHCLASS_SQUARE_H

class Square : public Oscillator {
public:
  Square(float frequency, float amplitude, int sampleRate);
  ~Square();
};

#endif // INC_04C_SYNTHCLASS_SQUARE_H
