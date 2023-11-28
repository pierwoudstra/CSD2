#include "Instrument.h"
#include "StringedInstrument.h"

int main() {
  StringedInstrument piano("ping", 88, "copper", "hammer");
  StringedInstrument guitar("tok", 36, "steel", "plectrum");

  piano.play(1, 127);
  piano.play(5, 48);
  guitar.play(1, 28);
}
