#include <iostream>

class Instrument {
  public:

    Instrument(std::string initSound = "bop") {
      sound = initSound;
    }

    void setSound(std::string newSound){
      sound = newSound;
    }

    std::string getSound() {
      return sound;
    }

    void play( int numOfRepeats = 1 ) {
      for ( int i = 0; i < numOfRepeats; i++ ) {
        std::cout << getSound() << std::endl;
      }
    }

  private:

    std::string sound;

};

int main() {
  Instrument gong = Instrument("gonngg");
  Instrument piano = Instrument("tangg");

  piano.setSound("ping");
  piano.play(5);

  gong.play();
}
