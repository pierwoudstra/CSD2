#include <iostream>
#include "Instrument.h"

class StringedInstrument : public Instrument {
  private:
    std::string stringMaterial;
    float bodySize;

  public:
    StringedInstrument( std::string initSound, int initRange, std::string initStringMaterial, float initBodySize );
};
