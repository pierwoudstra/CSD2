#include <iostream>
#include "instrument.h"

Instrument::Instrument( std::string initSound, int initRange ) {
    sound = initSound;
    range = initRange;
}

void Instrument::setSound( std::string newSound ) {
    sound = newSound;
}

void Instrument::setRange( int newRange ) {
    range = newRange;
}

std::string Instrument::getSound() {
    return sound;
}

void Instrument::play( int numOfRepeats = 1 ) {
    for ( int i = 0; i < numOfRepeats; i++ ) {
        std::cout << getSound() << std::endl;
    }
}