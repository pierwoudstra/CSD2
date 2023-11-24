#include <iostream>
#include "StringedInstrument.h"

StringedInstrument::StringedInstrument( std::string initSound, int initRange, std::string initStringMaterial, float initBodySize ) : Instrument ( initSound, initRange ) {
        sound = initSound;
        range = initRange;
        
        stringMaterial = initStringMaterial;
        bodySize = initBodySize;
}
