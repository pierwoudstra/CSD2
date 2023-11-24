#include "StringedInstrument.h"
#include <iostream>

StringedInstrument::StringedInstrument(std::string initSound, int initRange,
                                       std::string initStringMaterial,
                                       std::string initExciter)
    : Instrument(initSound, initRange) {

  sound = initSound;
  range = initRange;

  stringMaterial = initStringMaterial;
  exciter = initExciter;
}
