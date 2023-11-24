#include <iostream>

class Instrument {
  public:

    Instrument( std::string initSound, int initRange );
    void setSound( std::string newSound );
    void setRange( int newRange );
    std::string getSound();
    void play( int numOfRepeats = 1 );

  protected:

    std::string sound;
    int range;

};