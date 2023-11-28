#include "Instrument.h"
#include <iostream>

Instrument::Instrument(std::string initSound, int initRange) {
  sound = initSound;
  range = initRange;
}

void Instrument::setSound(std::string newSound) { sound = newSound; }

void Instrument::setRange(int newRange) { range = newRange; }

std::string Instrument::getSound() { return sound; }

int Instrument::getRange() { return range; }

void Instrument::play(int numOfRepeats, int pitch) {
  if (pitch <= getRange() && pitch >= 0) {
    for (int i = 0; i < numOfRepeats; i++) {
      std::cout << getSound() << "! pitch: " << pitch << std::endl;
    }
  } else {
    std::cout << "sorry, please choose a pitch inside the note range"
              << std::endl;
  }
}
