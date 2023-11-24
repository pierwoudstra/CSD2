#include "Instrument.h"
#include <iostream>

#ifndef STRINGEDINSTRUMENT_H
#define STRINGEDINSTRUMENT_H

class StringedInstrument : public Instrument {
public:
  StringedInstrument(std::string initSound, int initRange,
                     std::string initStringMaterial, std::string initExciter);
  ~StringedInstrument();

private:
  std::string stringMaterial;
  std::string exciter;
};

#endif // STRINGEDINSTRUMENT_H
