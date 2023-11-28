#include <iostream>

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

class Instrument {
public:
  Instrument(std::string initSound, int initRange);
  void setSound(std::string newSound);
  void setRange(int newRange);
  std::string getSound();
  int getRange();
  void play(int numOfRepeats, int pitch);

protected:
  std::string sound;
  int range;
};

#endif // INSTRUMENT_H
