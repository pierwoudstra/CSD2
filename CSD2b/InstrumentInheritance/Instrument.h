#include <iostream>

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

class Instrument {
public:
  Instrument(std::string initSound, int initRange);
  ~Instrument();
  void setSound(std::string newSound);
  void setRange(int newRange);
  std::string getSound();
  void play(int numOfRepeats);

protected:
  std::string sound;
  int range;
};

#endif // INSTRUMENT_H
